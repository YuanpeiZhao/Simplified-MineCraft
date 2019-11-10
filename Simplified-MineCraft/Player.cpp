#include "Player.h"



Player::Player(glm::vec3 pos, glm::vec3 rot)
{
	position = pos;
	rotation = glm::normalize(rot);
	pitch = 0;
	yaw = 0;
	step = 5.0f;
	mouseSensitivity = 1.0f;	
	collider = new Collider(pos, 1.5f, 0.2f);
}


Player::~Player()
{
}

void Player::Update()
{	
	Ground();
	Collision();
	position += velocity * DeltaTime;
}

void Player::Move(glm::vec3 dir, float dis)
{	
	position += dis * dir;     
}

void Player::Jump()
{
	
	if (isGrounded)
	{
		isGrounded = false;
		velocity.y =  6.0f;
	}
}

void Player::Ground()
{	
	if(!isGrounded){		
		velocity.y -= gravity * DeltaTime;		
	}
}

void Player::Collision()
{
	collider->UpdateCenter(position);
	collider->bGround = false;
	for (Cube cube : cubeList) {
		if (collider->CollisionDetection(cube, velocity, x)) {
			//position -= velocity.x * DeltaTime * xAxis;
			velocity.x = 0;
		}			
		if (collider->CollisionDetection(cube, velocity, y))
		{
			velocity.y = 0;
		}
		if (collider->CollisionDetection(cube, velocity, z)) {
			//position -= velocity.z * DeltaTime * zAxis;
			velocity.z = 0;
		}
	}	
	isGrounded = collider->bGround;
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
	glm::vec4 t =  glm::rotate(yaw, yAxis)* glm::rotate( pitch, xAxis) * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)  ;
	rotation = glm::vec3(t);
}

bool Collider::CollisionDetection(Cube cube, glm::vec3 velocity, Dir dir)
{
	switch (dir)
	{
	case x:
		if (abs(center.z - cube.position.z) > rH || abs(center.y - cube.position.y) > rV)
			return false;
		else {
			if (abs(center.x + velocity.x * DeltaTime - cube.position.x) <= rH)
				return true;
			else
				return false;
		}
		break;
	case y:
		if (velocity.y <= 0 && center.y - 0.5 * height <= 0) {
			bGround = true;
			return true;
		}
		if (abs(center.z - cube.position.z) > rH || abs(center.x - cube.position.x) > rH) {
			return false;
		}
		else {
			if (velocity.y <= 0 && center.y - cube.position.y > 0 && center.y - cube.position.y <= rV + 0.1f) {
				bGround = true;
				return true;
			}
			else if(velocity.y > 0 && cube.position.y - center.y > 0 && cube.position.y - center.y <= rV)
				return true;
			else
				return false;
		}
		break;
	case z:
		if (abs(center.x - cube.position.x) > rH || abs(center.y - cube.position.y) > rV)
			return false;
		else {
			if (abs(center.z + velocity.z * DeltaTime - cube.position.z) <= rH)
				return true;
			else
				return false;
		}
		break;
	default:
		return false;
		break;
	}
}
