#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> //for pi
#include "GenCubes.h"
#include "Cubes.h"

static int N = 50;

std::vector<Cube> cubeList;

float basic[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
};

void init_map()
{
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(0.0f, 0.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(0.0f, 1.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(0.0f, -1.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(1.0f, 0.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(1.0f, 1.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(1.0f, -1.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(-1.0f, 0.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(-1.0f, 1.0f, 0.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(-1.0f, -1.0f, 0.0f)));

	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(0.0f, 2.0f, 1.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(1.0f, 2.0f, 1.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(-1.0f, 2.0f, 1.0f)));

	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(0.0f, 0.0f, 2.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(1.0f, 0.0f, 2.0f)));
	cubeList.push_back(Cube(GRASS_CUBE, glm::vec3(-1.0f, 0.0f, 2.0f)));
}

GLuint create_cube_vbo()
{
	//Declare a vector to hold N vertices
	float surf_verts[8 * 36 * 20];

	for (int i = 0; i < cubeList.size(); i++)
	{
		for (int j = 0; j < 36; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (k < 3)
				{
					surf_verts[36 * 8 * i + 8 * j + k] = basic[8 * j + k] + cubeList[i].position[k];
				}
				else
				{
					surf_verts[36 * 8 * i + 8 * j + k] = basic[8 * j + k];
				}
			}
		}
	}

	GLuint vbo;
	glGenBuffers(1, &vbo); //Generate vbo to hold vertex attributes for triangle.

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //Specify the buffer where vertex attribute data is stored.

	//Upload from main memory to gpu memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(surf_verts), surf_verts, GL_STATIC_DRAW);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); //unbind the vao

	return vao;
}

void draw_cubes(GLuint vao)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 36 * cubeList.size());
}
