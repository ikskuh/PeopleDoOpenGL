#include <GL/gl3w.h>
#include <stb/stb_image.h>
#include <cstdint>

//! Aktuelle Zeit seit Start in Millisekunden
extern uint32_t timer();

//! Lädt eine Textdatei als nullterminierter String
char const * loadtxt(char const * fileName);

void init()
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
