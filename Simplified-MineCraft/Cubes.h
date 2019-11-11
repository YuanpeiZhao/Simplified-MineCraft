#ifndef __CUBES_H__
#define __CUBES_H__

#include <glm/glm.hpp>

#define GRASS_CUBE 0
#define TREE_CUBE 1
#define LEAF_CUBE 2
#define WATER_CUBE 3

using namespace glm;


class Cube {
public:
	vec3 position;
	int type;

	Cube(int type, vec3 position);
	
};

#endif