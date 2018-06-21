#pragma once

#include "glm/glm.hpp"

class Vertex;
class HalfEdge;
class Face;

class HalfEdge
{
public:
	glm::vec3 as_vector() const;

	unsigned int id;
	Vertex* vert;   // The vertex the half edge is starting at
	Face* face;     // The face the half-edge borders
	HalfEdge* next; // The next half-edge around the face
	HalfEdge* pair; // The oppositely oriented adjacent half-edge
};

