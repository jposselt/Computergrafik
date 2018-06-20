#pragma once

#include "Vector3f.h"

class HalfEdge;

class Vertex
{
public:
	Vertex();
	~Vertex();

	int id;
	Vector3f position; // The 3d position of this vertex
	Vector3f normal;   // The normal of this vertex
	HalfEdge* e;       // One of the half-edges emantating from the vertex
};

