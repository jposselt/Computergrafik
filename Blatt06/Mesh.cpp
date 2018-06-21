#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::calculate_normals()
{
}

bounds Mesh::get_bounds() const
{
	bounds b;
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
