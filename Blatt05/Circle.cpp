#include "Circle.h"

const double Circle::defaultRadius(1.0);


Circle::Circle(cg::GLSLProgram & prog)
	: Circle(prog, Circle::defaultRadius)
{
}

Circle::Circle(cg::GLSLProgram & prog, double radius)
	: Circle(prog, radius, Circle::nEdgesDefault)
{
}

Circle::Circle(cg::GLSLProgram & prog, double radius, unsigned int edges)
	: VertexArrayObject(prog, false, GL_LINES), radius(radius), nEdges(edges)
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

std::vector<glm::vec3> Circle::setColors(const glm::vec3& color)
{
	std::vector<glm::vec3> colors;
	for (int i = 0; i <= nEdges; ++i) {
		colors.push_back(color);
	}
	return colors;
}

std::vector<GLuint> Circle::setIndices()
{
	std::vector<GLuint> indices;
	for (int i = 0; i < nEdges; ++i) {
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	return indices;
}