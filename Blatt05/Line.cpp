#include "Line.h"

Line::Line(cg::GLSLProgram & prog, glm::vec3 start, glm::vec3 end)
	: VertexArrayObject(prog, false, GL_LINES), start(start), end(end)
{
}

Line::~Line()
{
}

std::vector<glm::vec3> Line::setVertices()
{
	std::vector<glm::vec3> vertices;
	vertices.push_back(start);
	vertices.push_back(end);
	return vertices;
}

std::vector<glm::vec3> Line::setColors(const glm::vec3 & color)
{
	std::vector<glm::vec3> colors;
	colors.push_back(color);
	colors.push_back(color);
	return colors;
}

std::vector<GLuint> Line::setIndices()
{
	std::vector<GLuint> indices;
	indices.push_back(0);
	indices.push_back(1);
	return indices;
}
