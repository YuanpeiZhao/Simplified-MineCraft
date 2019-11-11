#include "Skybox.h"

GLuint create_skybox_vbo()
{
   const float cube_verts[] = { -1.0f,-1.0f,-1.0f,
                                 -1.0f,-1.0f, 1.0f,
                                 -1.0f, 1.0f, 1.0f,
                                 1.0f, 1.0f,-1.0f,
                                 -1.0f,-1.0f,-1.0f,
                                 -1.0f, 1.0f,-1.0f,
                                 1.0f,-1.0f, 1.0f,
                                 -1.0f,-1.0f,-1.0f,
                                 1.0f,-1.0f,-1.0f,
                                 1.0f, 1.0f,-1.0f,
                                 1.0f,-1.0f,-1.0f,
                                 -1.0f,-1.0f,-1.0f,
                                 -1.0f,-1.0f,-1.0f,
                                 -1.0f, 1.0f, 1.0f,
                                 -1.0f, 1.0f,-1.0f,
                                 1.0f,-1.0f, 1.0f,
                                 -1.0f,-1.0f, 1.0f,
                                 -1.0f,-1.0f,-1.0f,
                                 -1.0f, 1.0f, 1.0f,
                                 -1.0f,-1.0f, 1.0f,
                                 1.0f,-1.0f, 1.0f,
                                 1.0f, 1.0f, 1.0f,
                                 1.0f,-1.0f,-1.0f,
                                 1.0f, 1.0f,-1.0f,
                                 1.0f,-1.0f,-1.0f,
                                 1.0f, 1.0f, 1.0f,
                                 1.0f,-1.0f, 1.0f,
                                 1.0f, 1.0f, 1.0f,
                                 1.0f, 1.0f,-1.0f,
                                 -1.0f, 1.0f,-1.0f,
                                 1.0f, 1.0f, 1.0f,
                                 -1.0f, 1.0f,-1.0f,
                                 -1.0f, 1.0f, 1.0f,
                                 1.0f, 1.0f, 1.0f,
                                 -1.0f, 1.0f, 1.0f,
                                 1.0f,-1.0f, 1.0f };

   GLuint vbo;
   glGenBuffers(1, &vbo); // Generate vbo to hold vertex attributes for triangle

   glBindBuffer(GL_ARRAY_BUFFER, vbo); //specify the buffer where vertex attribute data is stored
   
   //upload from main memory to gpu memory
   glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verts), &cube_verts[0], GL_STATIC_DRAW);

   return vbo;
}

GLuint create_skybox_vao()
{
   GLuint vao;

   //generate vao id to hold the mapping from attrib variables in shader to memory locations in vbo
   glGenVertexArrays(1, &vao);

   //binding vao means that bindbuffer, enablevertexattribarray and vertexattribpointer 
   // state will be remembered by vao
   glBindVertexArray(vao);

   GLuint vbo = create_skybox_vbo();

   const GLint pos_loc = 0; //see also InitShader.cpp line 164

   glEnableVertexAttribArray(pos_loc); //enable the position attribute

   //tell opengl how to get the attribute values out of the vbo (stride and offset)
   glVertexAttribPointer(pos_loc, 3, GL_FLOAT, false, 3*sizeof(float), 0);
   glBindVertexArray(0); //unbind the vao

   return vao;
}

void draw_skybox(GLuint vao)
{
   glDrawArrays(GL_TRIANGLES, 0, 36);
}