#include "Face.h"
#include "HalfEdge.h"
#include "Vertex.h"

Face::Face()
{
}

Face::~Face()
{
}

void Face::calculate_normal()
{
}

glm::vec3 Face::centroid() const
{
	glm::vec3 centroid(0.0f);

	HalfEdge *e0 = e;
	int n = 0;
	do {
		centroid += e0->vert->position;
		n++;
		e0 = e0->next;
	} while (e0 != e);
	centroid /= n;

	return centroid;
}
