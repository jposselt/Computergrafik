#pragma once

#include "Vector3f.h"

class Vertex;
class HalfEdge;
class Face;

class HalfEdge
{
public:
	Vector3f as_vector() const;

	int id;
	Vertex* vert;  // The vertex at the end of the half-edge
	Face* f;        // The face the half-edge borders
	HalfEdge* next; // The next half-edge around the face
	HalfEdge* pair; // The oppositely oriented adjacent half-edge
};

