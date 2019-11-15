#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> //for pi
#include <iostream>
#include <map>
#include "GenCubes.h"

float surf_verts[9 * 36 * 3000];
float trans_surf_verts[9 * 36 * 200];

float basic[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
};

GLuint my_cube_vao;
GLuint my_cube_vbo;

GLuint my_trans_cube_vao;
GLuint my_trans_cube_vbo;

void init_map()
{

	for (int i = -20; i < 20; i++)
	{
		for (int j = -20; j < 20; j++)
		{
			cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(float(i), 0.0f, float(j))));
		}
	}
	
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(0.0f, 3.0f, 6.0f)));

	cubeList.push_back(Cube(LEAF_CUBE, glm::vec3(0.0f, 1.0f, 0.0f)));
	cubeList.push_back(Cube(LEAF_CUBE, glm::vec3(0.0f, -1.0f, 0.0f)));
	cubeList.push_back(Cube(LEAF_CUBE, glm::vec3(1.0f, 1.0f, 0.0f)));
	cubeList.push_back(Cube(LEAF_CUBE, glm::vec3(1.0f, -1.0f, 0.0f)));
	cubeList.push_back(Cube(LEAF_CUBE, glm::vec3(-1.0f, 1.0f, 0.0f)));
	cubeList.push_back(Cube(LEAF_CUBE, glm::vec3(-1.0f, -1.0f, 0.0f)));

	cubeList.push_back(Cube(TREE_CUBE, glm::vec3(0.0f, 1.0f, 2.0f)));
	cubeList.push_back(Cube(TREE_CUBE, glm::vec3(1.0f, 1.0f, 2.0f)));
	cubeList.push_back(Cube(TREE_CUBE, glm::vec3(-1.0f, 1.0f, 2.0f)));

	translucentCubeList.push_back(Cube(WATER_CUBE, glm::vec3(0.0f, 2.0f, 1.0f)));
	translucentCubeList.push_back(Cube(WATER_CUBE, glm::vec3(1.0f, 2.0f, 1.0f)));
	translucentCubeList.push_back(Cube(WATER_CUBE, glm::vec3(-1.0f, 2.0f, 1.0f)));
}

GLuint create_cube_vbo()
{
	//Read general cubeList to verts
	for (int i = 0; i < cubeList.size(); i++)
	{
		for (int j = 0; j < 36; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (k < 3)
				{
					surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k] + cubeList[i].position[k];
				}
				else if(k < 8)
				{
					surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k];
				}
				else
				{
					surf_verts[36 * 9 * i + 9 * j + k] = float(cubeList[i].type);
				}
			}
		}
	}

	GLuint vbo;
	glGenBuffers(1, &vbo); //Generate vbo to hold vertex attributes for triangle.

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //Specify the buffer where vertex attribute data is stored.

	//Upload from main memory to gpu memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(surf_verts), surf_verts, GL_DYNAMIC_DRAW);

	my_cube_vbo = vbo;
	return vbo;
}

GLuint create_cube_vao()
{
	GLuint vao;

	//Generate vao id to hold the mapping from attrib variables in shader to memory locations in vbo
	glGenVertexArrays(1, &vao);

	//Binding vao means that bindbuffer, enablevertexattribarray and vertexattribpointer state will be remembered by vao
	glBindVertexArray(vao);

	GLuint vbo = create_cube_vbo();

	const GLint pos_loc = 0; //See also InitShader.cpp line 164.

	glEnableVertexAttribArray(pos_loc); //Enable the position attribute.

	//Tell opengl how to get the attribute values out of the vbo (stride and offset).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0); //unbind the vao

	my_cube_vao = vao;
	return vao;
}

GLuint create_trans_cube_vbo()
{
	//Read waterList to verts
	for (int i = 0; i < translucentCubeList.size(); i++)
	{
		for (int j = 0; j < 36; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (k < 3)
				{
					trans_surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k] + translucentCubeList[i].position[k];
				}
				else if (k < 8)
				{
					trans_surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k];
				}
				else
				{
					trans_surf_verts[36 * 9 * i + 9 * j + k] = float(translucentCubeList[i].type);
				}
			}
		}
	}

	GLuint vbo;
	glGenBuffers(1, &vbo); //Generate vbo to hold vertex attributes for triangle.

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //Specify the buffer where vertex attribute data is stored.

	//Upload from main memory to gpu memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(trans_surf_verts), trans_surf_verts, GL_DYNAMIC_DRAW);

	my_trans_cube_vbo = vbo;
	return vbo;
}

GLuint create_trans_cube_vao()
{
	GLuint vao;

	//Generate vao id to hold the mapping from attrib variables in shader to memory locations in vbo
	glGenVertexArrays(1, &vao);

	//Binding vao means that bindbuffer, enablevertexattribarray and vertexattribpointer state will be remembered by vao
	glBindVertexArray(vao);

	GLuint vbo = create_trans_cube_vbo();

	const GLint pos_loc = 0; //See also InitShader.cpp line 164.

	glEnableVertexAttribArray(pos_loc); //Enable the position attribute.

	//Tell opengl how to get the attribute values out of the vbo (stride and offset).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0); //unbind the vao

	my_trans_cube_vao = vao;
	return vao;
}

GLuint create_plane_vbo()
{
	//Declare a vector to hold N vertices
	float verts[8*6] = {
	-100.0f, -0.5f, -100.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	 100.0f, -0.5f,  100.0f,  0.0f,  1.0f,  0.0f,  200.0f,  200.0f,
	-100.0f, -0.5f,  100.0f,  0.0f,  1.0f,  0.0f,  0.0f,  200.0f,
	-100.0f, -0.5f, -100.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	 100.0f, -0.5f, -100.0f,  0.0f,  1.0f,  0.0f,  200.0f,  0.0f,
	 100.0f, -0.5f,  100.0f,  0.0f,  1.0f,  0.0f,  200.0f,  200.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo); //Generate vbo to hold vertex attributes for triangle.

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //Specify the buffer where vertex attribute data is stored.

	//Upload from main memory to gpu memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	return vbo;
}

GLuint create_plane_vao()
{
	GLuint vao;

	//Generate vao id to hold the mapping from attrib variables in shader to memory locations in vbo
	glGenVertexArrays(1, &vao);

	//Binding vao means that bindbuffer, enablevertexattribarray and vertexattribpointer state will be remembered by vao
	glBindVertexArray(vao);

	GLuint vbo = create_plane_vbo();

	const GLint pos_loc = 0; //See also InitShader.cpp line 164.

	glEnableVertexAttribArray(pos_loc); //Enable the position attribute.

	//Tell opengl how to get the attribute values out of the vbo (stride and offset).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); //unbind the vao

	return vao;
}

void sortTranslucentCubeVBO(std::map<float, glm::vec3> sorted)
{
	glBindVertexArray(my_trans_cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, my_trans_cube_vbo);

	int i = 0;
	for (std::map<float, glm::vec3>::iterator it = sorted.begin(); it != sorted.end(); it++)
	{
		for (int j = 0; j < 36; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (k < 3)
				{
					trans_surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k] + it->second[k];
				}
				else if (k < 8)
				{
					trans_surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k];
				}
				else
				{
					trans_surf_verts[36 * 9 * i + 9 * j + k] = float(WATER_CUBE);
				}
			}
		}
		i++;
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(trans_surf_verts), trans_surf_verts);
	glBindVertexArray(0);
}

void redefineCubeVBO()
{
	glBindVertexArray(my_cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, my_cube_vbo);

	for (int i = 0; i < cubeList.size(); i++)
	{
		for (int j = 0; j < 36; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (k < 3)
				{
					surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k] + cubeList[i].position[k];
				}
				else if (k < 8)
				{
					surf_verts[36 * 9 * i + 9 * j + k] = basic[8 * j + k];
				}
				else
				{
					surf_verts[36 * 9 * i + 9 * j + k] = float(cubeList[i].type);
				}
			}
		}
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(surf_verts), surf_verts);
	glBindVertexArray(0);
}

void draw_cubes(GLuint vao)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 36 *  cubeList.size());
}

void draw_trans_cubes(GLuint vao)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 36 * translucentCubeList.size());
}

void draw_plane(GLuint vao)
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
