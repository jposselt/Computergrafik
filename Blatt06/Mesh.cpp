#include "Mesh.h"

Mesh::Mesh()
{
}

/// <summary>
/// Finalizes an instance of the <see cref="Mesh"/> class.
/// </summary>
Mesh::~Mesh()
{
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i)) {
			delete vertices.at(i);
			vertices.at(i) = nullptr;
		}
	}

	for (int i = 0; i < edges.size(); i++) {
		if (edges.at(i)) {
			delete edges.at(i);
			edges.at(i) = nullptr;
		}
	}

	for (int i = 0; i < faces.size(); i++) {
		if (faces.at(i)) {
			delete faces.at(i);
			faces.at(i) = nullptr;
		}
	}
}

/// <summary>
/// Calculates the normal of each vertex as the average of surrounding face normals overwriting existing values.
/// </summary>
void Mesh::calculateNormals()
{
	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		glm::vec3 vertexNormal(0.0f);
		
		HalfEdge *edge = *iter;

		do {
			glm::vec3 faceNormal = glm::normalize(glm::cross(edge->pair->next->as_vector(), edge->as_vector()));
			vertexNormal += faceNormal;
			edge->pair->next->face->normal = faceNormal;
			edge = edge->pair->next;
		} while (edge != *iter);

		(*iter)->normal = glm::normalize(vertexNormal);

	}
}

/// <summary>
/// Gets the bounds.
/// </summary>
/// <returns></returns>
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
