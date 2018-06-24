#pragma once

#include <vector>

#include "Vertex.h"
#include "HalfEdge.h"
#include "Face.h"

typedef struct {
	float max_x;
	float max_y;
	float max_z;
	float min_x;
	float min_y;
	float min_z;
} Bounds;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void calculateNormals();
	Bounds getBounds() const;

	std::vector<Vertex*> vertices;
	std::vector<HalfEdge*> edges;
	std::vector<Face*> faces;
};

