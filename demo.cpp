// our framework
#include "common.h"

// OpenGL
#include <GL/gl3w.h>

// for textures
#include <stb/stb_image.h>

// for useful math (GLSL-like arithmetic in c++!)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void init()
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
