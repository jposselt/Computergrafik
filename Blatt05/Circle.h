#pragma once
#include "VertexArrayObject.h"
class Circle :
	public VertexArrayObject
{
public:
	Circle(cg::GLSLProgram & prog);
	Circle(cg::GLSLProgram & prog, double radius);
	Circle(cg::GLSLProgram & prog, double radius, unsigned int edges);
	~Circle();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors(const glm::vec3& color);
	std::vector<GLuint> setIndices();

private:
	unsigned int nEdges;
	double radius;

	/* Class constants */
	static const unsigned int nEdgesDefault = 360;
	static const double defaultRadius;
};

