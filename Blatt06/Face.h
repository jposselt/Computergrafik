#pragma once

#include "Vector3f.h"

class HalfEdge;

class Face
{
public:
	Face();
	~Face();

	void calculate_normal();
	Vector3f centroid() const;

	int id;
	HalfEdge* e;     // One of the half-edges bordering the face
	Vector3f normal; // Normal vector of this face
};

