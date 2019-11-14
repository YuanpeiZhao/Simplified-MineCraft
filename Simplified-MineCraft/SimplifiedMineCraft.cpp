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

#include "Skybox.h"
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

static const std::string tree_log_texture_name = "textures/treeBlock/oak_log.png";
GLuint tree_log_texture_id = -1;
static const std::string tree_log_top_texture_name = "textures/treeBlock/oak_log_top.png";
GLuint tree_log_top_texture_id = -1;
static const std::string tree_leaves_texture_name = "textures/treeBlock/oak_leaves.png";
GLuint tree_leaves_texture_id = -1;

static const std::string water_still_texture_name = "textures/waterBlock/water_still.png";
GLuint water_still_texture_id = -1;

static const std::string skybox_name[15] = { "cubemap\\01", "cubemap\\02", "cubemap\\03", "cubemap\\04", "cubemap\\05", "cubemap\\06", "cubemap\\07", "cubemap\\08", 
"cubemap\\09", "cubemap\\10", "cubemap\\11",  "cubemap\\12",  "cubemap\\13",  "cubemap\\14",  "cubemap\\15", };
GLuint skybox_id[15] = { -1 }; //Texture id for cubemap

//Cube files and IDs
static const std::string cube_vs("cube_vs.glsl");
static const std::string cube_fs("cube_fs.glsl");
GLuint cube_shader_program = -1;
GLuint cube_vao = -1;

//Plane files and IDs
static const std::string plane_vs("plane_vs.glsl");
static const std::string plane_fs("plane_fs.glsl");
GLuint plane_shader_program = -1;
GLuint plane_vao = -1;

//Skybox files and IDs
static const std::string skybox_vs("skybox_vs.glsl");
static const std::string skybox_fs("skybox_fs.glsl");
GLuint skybox_shader_program = -1;
GLuint skybox_vao = -1;

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

void draw_skybox(const glm::mat4& P, const glm::mat4& V)
{
	glUseProgram(skybox_shader_program);
	int PVM_loc = glGetUniformLocation(skybox_shader_program, "PVM");
	if (PVM_loc != -1)
	{
		glm::mat4 Msky = glm::scale(glm::vec3(5.0f));
		glm::mat4 PVM = P * V * Msky;
		PVM[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[0]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[1]);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[2]);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[3]);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[4]);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[5]);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[6]);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[7]);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[8]);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[9]);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[10]);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[11]);
	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[12]);
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[13]);
	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id[14]);

	int skybox01_loc = glGetUniformLocation(skybox_shader_program, "cubemap01");
	if (skybox01_loc != -1)
	{
		glUniform1i(skybox01_loc, 1); // we bound our texture to texture unit 1
	}
	int skybox02_loc = glGetUniformLocation(skybox_shader_program, "cubemap02");
	if (skybox02_loc != -1)
	{
		glUniform1i(skybox02_loc, 2); // we bound our texture to texture unit 1
	}
	int skybox03_loc = glGetUniformLocation(skybox_shader_program, "cubemap03");
	if (skybox03_loc != -1)
	{
		glUniform1i(skybox03_loc, 3); // we bound our texture to texture unit 1
	}
	int skybox04_loc = glGetUniformLocation(skybox_shader_program, "cubemap04");
	if (skybox04_loc != -1)
	{
		glUniform1i(skybox04_loc, 4); // we bound our texture to texture unit 1
	}
	int skybox05_loc = glGetUniformLocation(skybox_shader_program, "cubemap05");
	if (skybox05_loc != -1)
	{
		glUniform1i(skybox05_loc, 5); // we bound our texture to texture unit 1
	}
	int skybox06_loc = glGetUniformLocation(skybox_shader_program, "cubemap06");
	if (skybox06_loc != -1)
	{
		glUniform1i(skybox06_loc, 6); // we bound our texture to texture unit 1
	}
	int skybox07_loc = glGetUniformLocation(skybox_shader_program, "cubemap07");
	if (skybox07_loc != -1)
	{
		glUniform1i(skybox07_loc, 7); // we bound our texture to texture unit 1
	}
	int skybox08_loc = glGetUniformLocation(skybox_shader_program, "cubemap08");
	if (skybox08_loc != -1)
	{
		glUniform1i(skybox08_loc, 8); // we bound our texture to texture unit 1
	}
	int skybox09_loc = glGetUniformLocation(skybox_shader_program, "cubemap09");
	if (skybox09_loc != -1)
	{
		glUniform1i(skybox09_loc, 9); // we bound our texture to texture unit 1
	}
	int skybox10_loc = glGetUniformLocation(skybox_shader_program, "cubemap10");
	if (skybox10_loc != -1)
	{
		glUniform1i(skybox10_loc, 10); // we bound our texture to texture unit 1
	}
	int skybox11_loc = glGetUniformLocation(skybox_shader_program, "cubemap11");
	if (skybox11_loc != -1)
	{
		glUniform1i(skybox11_loc, 11); // we bound our texture to texture unit 1
	}
	int skybox12_loc = glGetUniformLocation(skybox_shader_program, "cubemap12");
	if (skybox12_loc != -1)
	{
		glUniform1i(skybox12_loc, 12); // we bound our texture to texture unit 1
	}
	int skybox13_loc = glGetUniformLocation(skybox_shader_program, "cubemap13");
	if (skybox13_loc != -1)
	{
		glUniform1i(skybox13_loc, 13); // we bound our texture to texture unit 1
	}
	int skybox14_loc = glGetUniformLocation(skybox_shader_program, "cubemap14");
	if (skybox14_loc != -1)
	{
		glUniform1i(skybox14_loc, 14); // we bound our texture to texture unit 1
	}
	int skybox15_loc = glGetUniformLocation(skybox_shader_program, "cubemap15");
	if (skybox15_loc != -1)
	{
		glUniform1i(skybox15_loc, 15); // we bound our texture to texture unit 1
	}

	glDepthMask(GL_FALSE);
	glBindVertexArray(skybox_vao);
	draw_skybox(skybox_vao);
	glDepthMask(GL_TRUE);
}

void draw_plane(const glm::mat4& P, const glm::mat4& V)
{
	glUseProgram(plane_shader_program);
	glm::mat4 R = glm::rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 M = R * glm::scale(glm::vec3(1.0f));

	int M_loc = glGetUniformLocation(plane_shader_program, "M");
	if (M_loc != -1)
	{
		glUniformMatrix4fv(M_loc, 1, false, glm::value_ptr(M));
	}

	int PVM_loc = glGetUniformLocation(plane_shader_program, "PVM");
	if (PVM_loc != -1)
	{
		glm::mat4 PVM = P * V * M;
		glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
	}

	// grassCube Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dirt_texture_id);

	int dirt_tex_loc = glGetUniformLocation(plane_shader_program, "dirt_tex");
	if (dirt_tex_loc != -1)
	{
		glUniform1i(dirt_tex_loc, 0);
	}

	glBindVertexArray(plane_vao);
	draw_plane(plane_vao);
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

	// grassCube Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dirt_texture_id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grass_cube_top_texture_id);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, grass_cube_side_texture_id);

	glUseProgram(cube_shader_program);
	int dirt_tex_loc = glGetUniformLocation(cube_shader_program, "dirt_tex");
	if (dirt_tex_loc != -1)
	{
		glUniform1i(dirt_tex_loc, 0);
	}

	int grass_top_tex_loc = glGetUniformLocation(cube_shader_program, "grass_top_tex");
	if (grass_top_tex_loc != -1)
	{
		glUniform1i(grass_top_tex_loc, 1);
	}

	int grass_side_tex_loc = glGetUniformLocation(cube_shader_program, "grass_side_tex");
	if (grass_side_tex_loc != -1)
	{
		glUniform1i(grass_side_tex_loc, 2);
	}

	// treeCube Textures
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, tree_log_texture_id);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, tree_log_top_texture_id);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, tree_leaves_texture_id);

	glUseProgram(cube_shader_program);
	int tree_log_tex_loc = glGetUniformLocation(cube_shader_program, "tree_log_tex");
	if (tree_log_tex_loc != -1)
	{
		glUniform1i(tree_log_tex_loc, 3);
	}

	int tree_log_top_tex_loc = glGetUniformLocation(cube_shader_program, "tree_log_top_tex");
	if (tree_log_top_tex_loc != -1)
	{
		glUniform1i(tree_log_top_tex_loc, 4);
	}

	int tree_leaves_tex_loc = glGetUniformLocation(cube_shader_program, "tree_leaves_tex");
	if (tree_leaves_tex_loc != -1)
	{
		glUniform1i(tree_leaves_tex_loc, 5);
	}

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, water_still_texture_id);

	glUseProgram(cube_shader_program);
	int water_still_tex_loc = glGetUniformLocation(cube_shader_program, "water_still_tex");
	if (water_still_tex_loc != -1)
	{
		glUniform1i(water_still_tex_loc, 6);
	}

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

	draw_skybox(P, V);
	draw_cubes(P, V);
	draw_plane(P, V);

	draw_gui();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();

	const int time_ms = glutGet(GLUT_ELAPSED_TIME);
	float time_sec = 0.001f * time_ms;

	glUseProgram(cube_shader_program);
	int time_loc = glGetUniformLocation(cube_shader_program, "time_sec");
	if (time_loc != -1)
	{
		glUniform1f(time_loc, time_sec);
	}

	glUseProgram(skybox_shader_program);
	time_loc = glGetUniformLocation(skybox_shader_program, "time_sec");
	if (time_loc != -1)
	{
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

	for (int i = 0; i < 15; i++)
	{
		skybox_id[i] = LoadCube(skybox_name[i]);
	}
	
	skybox_shader_program = InitShader(skybox_vs.c_str(), skybox_fs.c_str());
	cube_shader_program = InitShader(cube_vs.c_str(), cube_fs.c_str());
	plane_shader_program = InitShader(plane_vs.c_str(), plane_fs.c_str());

	init_map();

	skybox_vao = create_skybox_vao();
	cube_vao = create_cube_vao();
	plane_vao = create_plane_vao();

	ImGui_ImplGlut_Init(); // initialize the imgui system

	dirt_texture_id = LoadTexture(dirt_texture_name);
	grass_cube_top_texture_id = LoadTexture(grass_cube_top_texture_name);
	grass_cube_side_texture_id = LoadTexture(grass_cube_side_texture_name);

	tree_log_texture_id = LoadTexture(tree_log_texture_name);
	tree_log_top_texture_id = LoadTexture(tree_log_top_texture_name);
	tree_leaves_texture_id = LoadTexture(tree_leaves_texture_name);

	water_still_texture_id = LoadTexture(water_still_texture_name);
	
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