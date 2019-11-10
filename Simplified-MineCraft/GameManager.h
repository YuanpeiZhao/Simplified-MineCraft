#pragma once
#include "Cubes.h"
#include <vector>
#include <glm\glm.hpp>
#define yAxis glm::vec3(0.0f, 1.0f, 0.0f)
#define xAxis glm::vec3(1.0f, 0.0f, 0.0f)
#define zAxis glm::vec3(0.0f, 0.0f, 1.0f)
extern const int deltaTime;
extern const float DeltaTime;
extern std::vector<Cube> cubeList;
