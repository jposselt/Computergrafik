#pragma once

#include "glm/glm.hpp"

class HalfEdge;

class Vertex
{
public:
	Vertex();
	~Vertex();

	unsigned int id;
	glm::vec3 position; // The 3d position of this vertex
	glm::vec3 normal;   // The normal of this vertex
	HalfEdge* edge;        // One of the half-edges emantating from the vertex
};

