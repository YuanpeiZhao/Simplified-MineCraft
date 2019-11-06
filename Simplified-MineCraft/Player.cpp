#include "Player.h"



Player::Player(glm::vec3 pos, glm::vec3 rot)
{
	position = pos;
	rotation = glm::normalize(rot);
	pitch = 0;
	yaw = 0;
	step = 0.05f;
	mouseSensitivity = 1.0f;
}


Player::~Player()
{
}

void Player::Move(glm::vec3 dir, float dis)
{	
	position += dis * dir;
}



glm::vec3 Player::Target() {
	return position + rotation;
}

glm::vec3 Player::Up() {
	return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Player::Forward() {
	return glm::normalize(glm::cross(Up(), Right()));
}

glm::vec3 Player::Right() {
	return glm::normalize(glm::cross(rotation, Up()));
}

void Player::GetKey(unsigned char key)
{
	switch (key)
	{
	case 'w':
		Move(Forward(), step);
		break;
	case 's':
		Move(-Forward(), step);
		break;
	case 'a':
		Move(-Right(), step);
		break;
	case 'd':
		Move(Right(), step);
		break;
	
	default:
		break;
	}

}



void Player::OnMouseMove(int x, int y)
{
	x = x * mouseSensitivity;
	y = y * mouseSensitivity;
	yaw += x;
	pitch += y;
	
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	/*float Y = glm::radians(yaw);
	float P = glm::radians(pitch);
	rotation = glm::vec3(-sin(Y)*cos(P), sin(P), -cos(P) * cos(Y));*/
	glm::vec4 t =  glm::rotate(yaw, glm::vec3(0.0f, 1.0f, 0.0f))* glm::rotate( pitch, glm::vec3(1.0f,0.0f,0.0f)) * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)  ;
	rotation = glm::vec3(t);
}

