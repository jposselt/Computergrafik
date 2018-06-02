#pragma once
#include "VertexArrayObject.h"

class Circle :
	public VertexArrayObject
{
public:
	Circle(cg::GLSLProgram *prog);
	Circle(cg::GLSLProgram *prog, double radius);
	Circle(cg::GLSLProgram *prog, double radius, glm::vec3 color);
	~Circle();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors();
	std::vector<GLushort> setIndices();

private:
	unsigned int nEdges = 360;
	double radius;
	glm::vec3 color;
};

