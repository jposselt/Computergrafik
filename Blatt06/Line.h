#pragma once
#include "GeometryObject.h"

class Line :
	public GeometryObject
{
public:
	Line(cg::GLSLProgram& shader, glm::vec3 start, glm::vec3 end);
	~Line();

private:
	VertexArrayObject * geometry;
};

