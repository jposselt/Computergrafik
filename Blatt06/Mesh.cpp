#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::calculateNormals()
{
	for (auto iter = vertices.begin(); iter != vertices.end(); ++iter) {
		Vertex *vert = (*iter);
		HalfEdge *edge = vert->edge;

		glm::vec3 vertexNormal(0.0f);
		do {
			glm::vec3 faceNormal = glm::cross(edge->pair->next->as_vector(), edge->as_vector());
			edge->pair->next->face->normal = glm::normalize(faceNormal);
			vertexNormal += faceNormal;
			edge = edge->pair->next;
		} while (edge != vert->edge);
		vert->normal = glm::normalize(vertexNormal);
	}
}

Bounds Mesh::getBounds() const
{
	Bounds b;
	b.min_x = INFINITY;
	b.min_y = INFINITY;
	b.min_z = INFINITY;
	b.max_x = -INFINITY;
	b.max_y = -INFINITY;
	b.max_z = -INFINITY;

	for (auto vit = vertices.begin(); vit != vertices.end(); vit++) {
		glm::vec3 loc = (*vit)->position;
		if (loc.x < b.min_x) b.min_x = loc.x;
		if (loc.x > b.max_x) b.max_x = loc.x;
		if (loc.y < b.min_y) b.min_y = loc.y;
		if (loc.y > b.max_y) b.max_y = loc.y;
		if (loc.z < b.min_z) b.min_z = loc.z;
		if (loc.z > b.max_z) b.max_z = loc.z;
	}

	return b;
}
