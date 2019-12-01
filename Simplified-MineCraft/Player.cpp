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
	GetNearestCube(position);
	Ground();
	Collision();
	hand.PlayAnim();
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
	for (Cube cube : nearCubeList) {
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

glm::vec3 Player::GetTargetCube(int type)
{
	glm::vec3 pos = null;
	float dis = 1000.0f;  
	for (Cube cube : nearCubeList) {
		if (glm::dot(cube.position-position, rotation) > 0 && 
			PointToLine(cube.position, position, Target()) <= 0.7f && 
			glm::distance(cube.position, position) < dis) {
			pos = cube.position;
			dis = glm::distance(cube.position, position);
		}
	}
	if (pos == null)
		return null;
	if(type == 0)
		return pos;
	else if (type == 1) {
		std::vector<glm::vec3> posList;
		glm::vec3 a = position - pos;
		posList.push_back((a.x > 0 ? +1.0f : -1.0f) * xAxis + pos);
		posList.push_back((a.y > 0 ? +1.0f : -1.0f) * yAxis + pos);
		posList.push_back((a.z > 0 ? +1.0f : -1.0f) * zAxis + pos);
		for (glm::vec3 p : posList) {
			if (PointToLine(p, position, Target()) < 0.7f) {
				return p;
			}
		}
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
	glm::mat4 R = glm::rotate(yaw, yAxis)* glm::rotate(pitch, xAxis);
	glm::vec4 t =  R * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)  ;
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

Hand::Hand()
{
	angle = 0.0f;
	S = glm::scale(glm::vec3(0.1f, 0.1f, 0.8f));
	R = glm::rotate(0.0f, yAxis)* glm::rotate(0.0f + angle, xAxis);
	T = glm::translate(glm::vec3(0.0f));
	M = T * R * glm::translate(glm::vec3(0.15f, -0.15f, 0.0f)) * S;
	anim.count = 10;
	for (int i = 0; i < anim.count; i++) {
		anim.Angle[i] = i * 6;
	}
	anim.index = anim.count - 1;
}

Hand::~Hand()
{
}

void Hand::Update(glm::vec3 pos, float pitch, float yaw)
{
	R = glm::rotate(yaw, yAxis)* glm::rotate(pitch + angle, xAxis);
	T = glm::translate(pos);
	M = T * R * glm::translate(glm::vec3(0.15f, -0.15f, 0.0f)) * S;
}

void Hand::PlayAnim()
{
	if (anim_trigger) {				
		angle = anim.Angle[anim.index--];
		if (anim.index == 0) {
			anim.index = anim.count - 1;
			anim_trigger = false;			
		}
	}
}
