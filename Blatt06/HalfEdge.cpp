#include "HalfEdge.h"
#include "Vertex.h"

glm::vec3 HalfEdge::as_vector() const
{
	return glm::normalize( next->vert->position - vert->position );
}
