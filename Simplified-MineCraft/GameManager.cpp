#include "GameManager.h"

std::vector<Cube> translucentCubeList;
std::vector<Cube> cubeList;
std::vector<Cube> nearCubeList;
const int deltaTime = 16;
const float DeltaTime = 0.016f;
const float cycleTime = 15.0f;
const int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

void GetNearestCube(glm::vec3 pos)
{	
	nearCubeList.clear();
	for (Cube cube : cubeList)
	{
		if (glm::distance(cube.position, pos) <= COLLISION_DETECT_RANGE) {
			nearCubeList.push_back(cube);
		}	
	}
}

float PointToLine(glm::vec3 point, glm::vec3 lineBegin, glm::vec3 lineEnd)
{
	float theta = glm::acos(glm::dot(glm::normalize(point - lineBegin), glm::normalize(lineEnd - lineBegin)));
	float dis = glm::distance(point, lineBegin) * glm::sin(theta);
	return dis;
}
