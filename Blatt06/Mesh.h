#pragma once

#include <vector>

#include "Vertex.h"
#include "HalfEdge.h"
#include "Face.h"
#include "Vector3f.h"

typedef struct {
	float max_x;
	float max_y;
	float max_z;
	float min_x;
	float min_y;
	float min_z;
} bounds;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void calculate_normals();
	bounds get_bounds() const;

	std::vector<Vertex*> verteces;
	std::vector<HalfEdge*> edges;
	std::vector<Face*> faces;
};

