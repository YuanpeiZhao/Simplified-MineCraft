#include "Cubes.h"

Cube::Cube(int t, vec3 pos) {
	type = t;
	position = pos;
	health = 4;
}

bool Cube::operator==(const Cube & cube) const
{
	return position == cube.position;
}

bool Cube::operator==(const glm::vec3 & pos) const
{
	return position == pos;
}


