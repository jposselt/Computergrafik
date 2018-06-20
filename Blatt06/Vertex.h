#pragma once

#include "glm/glm.hpp"
#include "Vector3f.h"

class HalfEdge;

class Vertex
{
public:
	Vertex();
	~Vertex();

	int id;
	glm::vec3 position; // The 3d position of this vertex
	glm::vec3 normal;   // The normal of this vertex
	HalfEdge* e;       // One of the half-edges emantating from the vertex
};

