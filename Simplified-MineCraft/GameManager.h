#pragma once
#include "Cubes.h"
#include <vector>
#include <algorithm>
#include <glm\glm.hpp>
#define yAxis glm::vec3(0.0f, 1.0f, 0.0f)
#define xAxis glm::vec3(1.0f, 0.0f, 0.0f)
#define zAxis glm::vec3(0.0f, 0.0f, 1.0f)
#define null glm::vec3(-100.0f)
#define COLLISION_DETECT_RANGE 5
extern const int deltaTime;
extern const float DeltaTime;
extern const float cycleTime;
extern const int SHADOW_WIDTH, SHADOW_HEIGHT;
extern std::vector<Cube> cubeList;
extern std::vector<Cube> nearCubeList;
extern std::vector<Cube> translucentCubeList;

void GetNearestCube(glm::vec3 pos);
float PointToLine(glm::vec3 point, glm::vec3 lineBegin, glm::vec3 lineEnd);