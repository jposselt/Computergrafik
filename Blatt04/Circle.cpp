#include "Circle.h"


Circle::Circle(cg::GLSLProgram *prog)
	: Circle(prog, 1.0, glm::vec3(1.0f, 0.0f, 0.0f))
{
}

Circle::Circle(cg::GLSLProgram *prog, double radius)
	: Circle(prog, radius, glm::vec3(1.0f, 0.0f, 0.0f))
{
}

Circle::Circle(cg::GLSLProgram *prog, double radius, glm::vec3 color)
	: VertexArrayObject(prog), radius(radius), color(color)
{
}


Circle::~Circle()
{
}

std::vector<glm::vec3> Circle::setVertices()
{
	std::vector<glm::vec3> vertices;
	for (int i = 0; i <= nEdges; ++i) {
		GLfloat U = i / (float)nEdges;
		GLfloat theta = U * (glm::pi <float>() * 2);
		GLfloat x = cosf(theta);
		GLfloat z = sinf(theta);
		vertices.push_back(glm::vec3(x * radius, 0.0f, z * radius));
	}
	return vertices;
}

std::vector<glm::vec3> Circle::setColors()
{
	std::vector<glm::vec3> colors;
	for (int i = 0; i <= nEdges; ++i) {
		colors.push_back(color);
	}
	return colors;
}

std::vector<GLushort> Circle::setIndices()
{
	std::vector<GLushort> indices;
	for (int i = 0; i < nEdges; ++i) {
		indices.push_back(i);
		indices.push_back(i+1);
	}
	return indices;
}
