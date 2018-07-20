#include <GL/gl3w.h>
#include <SDL.h>
#include <SDL_opengl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "common.h"

static SDL_Window * window;

static SDL_GLContext context;

extern void init();

extern void render();

static uint32_t startup;

extern uint32_t timer()
{
	return SDL_GetTicks() - startup;
}

char const * loadtxt(char const * fileName)
{
	FILE * f = fopen(fileName, "r");
	if(f == nullptr)
		die("could not open file %s", fileName);

	fseek(f, 0, SEEK_END);
	size_t size = size_t(ftell(f));
	fseek(f, 0, SEEK_SET);

	char * data = reinterpret_cast<char*>(malloc(size + 1));
	if(data == nullptr)
		die("Could not allocate file storage for %s!", fileName);
	memset(data, 0, size + 1);

	size_t len = fread(data, 1, size, f);
	if(len != size)
		die("could not read file %s", fileName);
	fclose(f);
	return data;
}

static void APIENTRY debugCallback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam)
{
	(void)source;
	(void)type;
	(void)id;
	(void)userParam;

	fprintf(stderr, "[OpenGL] ");
	fwrite(message, size_t(length), 1, stderr);
	fprintf(stderr, "\n");
	fflush(stderr);

	// Instantly kill the system when a high severity error happens
	if(severity == GL_DEBUG_SEVERITY_HIGH)
		exit(EXIT_FAILURE);
}

int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		die("%s", SDL_GetError());
	atexit(SDL_Quit);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG | SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

	SDL_GL_SetSwapInterval(1);

	window = SDL_CreateWindow(
		"My First Shader",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(window == nullptr)
		die("Could not create window: %s", SDL_GetError());

	context = SDL_GL_CreateContext(window);
	if(context == nullptr)
		die("Could not create context: %s", SDL_GetError());

	if(gl3wInit() < 0)
		die("Could not initialize gl3w!");

	fprintf(stdout, "Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "Vendor:  %s\n", glGetString(GL_VENDOR));
	fprintf(stdout, "GLSL:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Check against some extensions we require

	int extcount = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &extcount);

	bool hasDSA = false;
	bool hasLog = false;
	for(unsigned int i = 0; i < size_t(extcount); i++)
	{
		char const * extension = reinterpret_cast<char const *>(glGetStringi(GL_EXTENSIONS, i));
		hasDSA |= !strcmp(extension, "GL_ARB_direct_state_access");
		hasLog |= !strcmp(extension, "GL_ARB_debug_output");
	}
	if(!hasDSA)
		die("GL_ARB_direct_state_access required!");

	if(hasLog)
	{
		glDebugMessageCallback(debugCallback, nullptr);
	}
	else
	{
		fprintf(stderr, "Warning: GL_ARB_debug_output not available, no errors or warnings will be logged!\n");
	}

	startup = SDL_GetTicks();

	init();

	bool active = true;
	while(active)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				active = false;
			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				active = false;
		}

		render();

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
