#include "Line.h"
#include "Constants.h"

Line::Line(cg::GLSLProgram& shader, glm::vec3 start, glm::vec3 end)
	: GeometryObject(nullptr, nullptr, nullptr, nullptr)
{
	geometry = new VertexArrayObject(shader, false, GL_LINES);

	std::vector<glm::vec3> vertices = { start, end };
	geometry->setVertices(vertices);

	std::vector<GLuint> indices = { 0, 1 };
	geometry->setIndices(indices);

	this->setGeometry(geometry);
	this->setGeometryColor(Constants::defaultColor());
}

Line::~Line()
{
	delete geometry;
}
