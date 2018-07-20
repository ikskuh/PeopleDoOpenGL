#include <GL/gl3w.h>
#include <SDL.h>
#include <SDL_opengl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace std;

#define die(msg, ...) do { fprintf(stderr, "%s:%d: ", __FILE__, __LINE__); fprintf(stderr, msg, ##__VA_ARGS__); fprintf(stderr, "\n"); exit(EXIT_FAILURE); } while(false);

SDL_Window * window;

SDL_GLContext context;

extern void init();

extern void render();

static uint32_t startup;

extern uint32_t timer()
{
	return SDL_GetTicks() - startup;
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