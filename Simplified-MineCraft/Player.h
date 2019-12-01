#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "GameManager.h"

enum Dir {
	x, y, z
};
class Collider {
public:

	glm::vec3 center;
	float height;
	float radius;
	float rH;
	float rV;
	bool bGround;
	Collider(glm::vec3 pos, float h, float r) {
		center = pos - 1 / 2 * h * yAxis;
		height = h;
		radius = r;
		rH = 0.5f + r;
		rV = 0.5f + 0.5f * h;
		bGround = false;
	}
	void UpdateCenter(glm::vec3 playerPos) {
		center = playerPos - 1 / 2 * height * yAxis;
	}
	bool CollisionDetection(Cube cube, glm::vec3 velocity, Dir dir);
};

class Hand {
public:
	Hand();
	~Hand();

	glm::mat4 R;
	glm::mat4 T;
	glm::mat4 S;
	glm::mat4 M;

	float angle;
	bool anim_trigger = false;
	struct Animation {
	 int count;
		float Angle[60];
		int index;
	}anim;

	void Update(glm::vec3 pos, float pitch, float yaw);
	void PlayAnim();
};

class Player
{
public:
	Player(glm::vec3 pos, glm::vec3 rot);
	~Player();

	float gravity = 9.8f;
	float step;
	float mouseSensitivity;
	float yaw;
	float pitch;

	bool isGrounded;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 velocity;
	
	glm::vec3 Up();
	glm::vec3 Target();
	glm::vec3 Forward();
	glm::vec3 Right();
	glm::vec3 GetTargetCube(int type);

	void Update();
	void Move(glm::vec3 dir, float dis);
	void Jump();
	void Ground();
	void Collision();

	void OnMouseMove(int x, int y);
	
	Collider* collider;
	Hand hand;
};

