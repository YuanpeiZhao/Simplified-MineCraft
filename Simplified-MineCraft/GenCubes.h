#ifndef __GENCUBES_H__
#define __GENCUBES_H__

#include <windows.h>
#include <GL/glew.h>

#include "GameManager.h"

GLuint create_cube_vao();
void draw_cubes(GLuint vao);
GLuint create_plane_vao();
void draw_plane(GLuint vao);
void init_map();

#endif