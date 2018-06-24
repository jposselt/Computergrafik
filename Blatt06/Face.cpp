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
	HalfEdge *e = this->edge;
	this->normal = glm::vec3(0.0f);
	do {
		this->normal += glm::cross(this->edge->as_vector(), this->edge->next->as_vector());
		e = e->next;
	} while (e != this->edge);
	this->normal = glm::normalize(this->normal);
}

glm::vec3 Face::centroid() const
{
	glm::vec3 centroid(0.0f);

	HalfEdge *e0 = edge;
	int n = 0;
	do {
		centroid += e0->vert->position;
		n++;
		e0 = e0->next;
	} while (e0 != edge);
	centroid /= n;

	return centroid;
}
