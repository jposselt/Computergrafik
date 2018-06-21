#pragma once

#include "glm/glm.hpp"

class HalfEdge;

class Face
{
public:
	Face();
	~Face();

	void calculate_normal();
	glm::vec3 centroid() const;

	unsigned int id;
	HalfEdge* edge;      // One of the half-edges bordering the face
	glm::vec3 normal; // Normal vector of this face
};

