#ifndef __GENCUBES_H__
#define __GENCUBES_H__

#include <windows.h>
#include <GL/glew.h>

#include "GameManager.h"

GLuint create_cube_vao();
GLuint create_trans_cube_vao();
GLuint create_plane_vao();
GLuint create_hand_vao();
GLuint create_ui_vao();

void draw_ui(GLuint vao);
void draw_hand(GLuint vao);
void draw_cubes(GLuint vao);
void draw_trans_cubes(GLuint vao);
void draw_plane(GLuint vao);
void init_map();
void sortTranslucentCubeVBO(std::map<float, glm::vec3> sorted);
void redefineCubeVBO();

void DeleteCube(glm::vec3 pos);
void AddCube(glm::vec3 pos, int type);

#endif