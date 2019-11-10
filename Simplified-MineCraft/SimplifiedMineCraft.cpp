#include <windows.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InitShader.h"
#include "LoadTexture.h"
#include "imgui_impl_glut.h"

#include "GenCubes.h"
#include "Player.h"
#include "GameManager.h"


//Texture files and IDs
static const std::string dirt_texture_name = "textures/grassBlock/dirt.png";
GLuint dirt_texture_id = -1;
static const std::string grass_cube_top_texture_name = "textures/grassBlock/grass_block_top.png";
GLuint grass_cube_top_texture_id = -1;
static const std::string grass_cube_side_texture_name = "textures/grassBlock/grass_block_side.png";
GLuint grass_cube_side_texture_id = -1;

//Cube files and IDs
static const std::string cube_vs("cube_vs.glsl");
static const std::string cube_fs("cube_fs.glsl");
GLuint cube_shader_program = -1;
GLuint cube_vao = -1;

//camera and viewport
float camangle = 0.0f;
glm::vec3 campos(3.0f, 3.0f, 3.0f);
float aspect = 1.0f;


float mouseX = 320.0f, mouseY = 320.0f;
float verAxis = 0.0f, horAxis = 0.0f;
Player player(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

void draw_gui()
{
	ImGui_ImplGlut_NewFrame();

	ImGui::Begin("Tool Bar", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderFloat3("Cam Pos", &campos[0], -5.0f, 5.0f);

	ImGui::End();

	ImGui::Render();
}

void draw_cubes(const glm::mat4& P, const glm::mat4& V)
{
	glUseProgram(cube_shader_program);
	glm::mat4 R = glm::rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 M = R * glm::scale(glm::vec3(1.0f));

	int M_loc = glGetUniformLocation(cube_shader_program, "M");
	if (M_loc != -1)
	{
		glUniformMatrix4fv(M_loc, 1, false, glm::value_ptr(M));
	}

	int PVM_loc = glGetUniformLocation(cube_shader_program, "PVM");
	if (PVM_loc != -1)
	{
		glm::mat4 PVM = P * V * M;
		glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dirt_texture_id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grass_cube_top_texture_id);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, grass_cube_side_texture_id);

	glBindVertexArray(cube_vao);
	draw_cubes(cube_vao);
}

// glut display callback function.
// This function gets called every time the scene gets redisplayed 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the back buffer

	//glm::mat4 V = glm::lookAt(campos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(camangle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 V = glm::lookAt(player.position, player.Target(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 P = glm::perspective(80.0f, aspect, 0.1f, 100.0f); //not affine

	draw_cubes(P, V);

	draw_gui();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();

	const int time_ms = glutGet(GLUT_ELAPSED_TIME);
	float time_sec = 0.001f * time_ms;

	glUseProgram(cube_shader_program);
	int time_loc = glGetUniformLocation(cube_shader_program, "time");
	if (time_loc != -1)
	{
		//double check that you are using glUniform1f
		glUniform1f(time_loc, time_sec);
	}
}

void Timer(int value) {	
	
		glm::vec3 dir = player.Forward() * verAxis * player.step + player.Right() * horAxis * player.step;
		player.velocity.x = dir.x;
		player.velocity.z = dir.z;
	
	

	player.Update();


	glutPostRedisplay();
	glutTimerFunc(deltaTime, Timer, 1);
}

void printGlInfo()
{
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void initOpenGl()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SPRITE);       // allows textured points
	glEnable(GL_PROGRAM_POINT_SIZE); //allows us to set point size in vertex shader
	glClearColor(0.65f, 0.65f, 0.65f, 1.0f);

	cube_shader_program = InitShader(cube_vs.c_str(), cube_fs.c_str());

	init_map();

	cube_vao = create_cube_vao();

	ImGui_ImplGlut_Init(); // initialize the imgui system

	dirt_texture_id = LoadTexture(dirt_texture_name);
	grass_cube_top_texture_id = LoadTexture(grass_cube_top_texture_name);
	grass_cube_side_texture_id = LoadTexture(grass_cube_side_texture_name);

	glUseProgram(cube_shader_program);
	int dirt_tex_loc = glGetUniformLocation(cube_shader_program, "Texture0");
	if (dirt_tex_loc != -1)
	{
		//double check that you are using glUniform1f
		glUniform1i(dirt_tex_loc, 0);
	}

	int grass_top_tex_loc = glGetUniformLocation(cube_shader_program, "Texture1");
	if (grass_top_tex_loc != -1)
	{
		//double check that you are using glUniform1f
		glUniform1i(grass_top_tex_loc, 1);
	}

	int grass_side_tex_loc = glGetUniformLocation(cube_shader_program, "Texture2");
	if (grass_side_tex_loc != -1)
	{
		//double check that you are using glUniform1f
		glUniform1i(grass_side_tex_loc, 2);
	}

	
	SetCursorPos(mouseX, mouseY);
}

// glut callbacks need to send keyboard and mouse events to imgui
void keyboard(unsigned char key, int x, int y)
{	
	switch (key)
	{
	case 'w':
		verAxis = 1.0f;
		break;
	case 's':
		verAxis = -1.0f;
		break;
	case 'a':
		horAxis = -1.0f;
		break;
	case 'd':
		horAxis = 1.0f;
		break;
	case 32:
		player.Jump();
		break;
	default:
		break;
	}
}

void keyboard_up(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		verAxis = 0.0f;
		break;
	case 's':
		verAxis = 0.0f;
		break;
	case 'a':
		horAxis = 0.0f;
		break;
	case 'd':
		horAxis = 0.0f;
		break;
	default:
		break;
	}
}

void motion(int x, int y)
{	
	player.OnMouseMove(mouseX - x, mouseY - y);
	mouseX = x;
	mouseY = y;
	
}



void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	aspect = (float)w / h;
}

int main(int argc, char** argv)
{
	//Configure initial window state
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 640);
	int win = glutCreateWindow("Simplified MineCraft");
	
	printGlInfo();

	//Register callback functions with glut. 
	glutDisplayFunc(display);
	
	glutTimerFunc(deltaTime, Timer, 1);	
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutPassiveMotionFunc(motion);

	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	initOpenGl();

	//Enter the glut event loop.
	glutMainLoop();
	glutDestroyWindow(win);
	return 0;
}