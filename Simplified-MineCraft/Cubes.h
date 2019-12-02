#ifndef __CUBES_H__
#define __CUBES_H__

#include <glm/glm.hpp>

#define GRASS_CUBE 0
#define TREE_CUBE 1
#define LEAF_CUBE 2
#define WATER_CUBE 3
#define SAND_CUBE 4
#define BRICK_CUBE 5
#define LIGHT_CUBE 6
#define ARM_CUBE 7

using namespace glm;


class Cube {
public:
	vec3 position;
	int type;
	int health;
	Cube(int type, vec3 position);

	bool operator==(const Cube &cube) const;
	bool operator==(const glm::vec3 &pos) const;
	
};

#endif