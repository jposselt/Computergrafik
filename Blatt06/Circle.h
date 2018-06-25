#pragma once
#include "GeometryObject.h"

class Circle :
	public GeometryObject
{
public:
	Circle(cg::GLSLProgram & shader, double radius, unsigned int edges);
	Circle(cg::GLSLProgram & shader, double radius);
	Circle(cg::GLSLProgram & shader);
	~Circle();

private:
	VertexArrayObject * geometry;
};

