#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <windows.h>
#include <GL/glew.h>

GLuint create_skybox_vao();
void draw_skybox(GLuint vao);

#endif
