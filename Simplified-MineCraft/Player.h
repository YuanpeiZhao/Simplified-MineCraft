#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>


class Player
{
public:
	Player(glm::vec3 pos, glm::vec3 rot);
	~Player();

	float step;
	float mouseSensitivity;
	float yaw;
	float pitch;
	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 Up();
	glm::vec3 Target();
	glm::vec3 Forward();
	glm::vec3 Right();
	
	void Move(glm::vec3 dir, float dis);


	void GetKey(unsigned char key);
	void OnMouseMove(int x, int y);
};