#pragma once

#include "glm/glm.hpp"
#include "Vector3f.h"

class HalfEdge;

class Face
{
public:
	Face();
	~Face();

	void calculate_normal();
	glm::vec3 centroid() const;

	int id;
	HalfEdge* e;      // One of the half-edges bordering the face
	glm::vec3 normal; // Normal vector of this face
};

