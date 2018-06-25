#include "Circle.h"
#include "Constants.h"

Circle::Circle(cg::GLSLProgram & shader, double radius, unsigned int edges)
	: GeometryObject(nullptr, nullptr, nullptr, nullptr)
{
	geometry = new VertexArrayObject(shader, false, GL_LINES);

	std::vector<glm::vec3> vertices;
	for (unsigned int i = 0; i <= edges; ++i) {
		GLfloat U = i / (float) edges;
		GLfloat theta = U * (glm::pi <float>() * 2);
		GLfloat x = cosf(theta);
		GLfloat z = sinf(theta);
		vertices.push_back(glm::vec3(x * radius, 0.0f, z * radius));
	}
	geometry->setVertices(vertices);

	std::vector<GLuint> indices;
	for (unsigned int i = 0; i < edges; ++i) {
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	geometry->setIndices(indices);

	this->setGeometry(geometry);
	this->setGeometryColor(Constants::defaultColor());
}

Circle::Circle(cg::GLSLProgram & shader, double radius)
	: Circle(shader, radius, Constants::edges)
{
}

Circle::Circle(cg::GLSLProgram & shader)
	: Circle(shader, Constants::radius, Constants::edges)
{
}

Circle::~Circle()
{
	delete geometry;
}
