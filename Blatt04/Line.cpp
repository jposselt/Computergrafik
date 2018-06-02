#include "Line.h"



Line::Line(cg::GLSLProgram *prog, glm::vec3 start, glm::vec3 end, glm::vec3 color)
	: VertexArrayObject(prog), start(start), end(end), color(color)
{
}

Line::Line(cg::GLSLProgram *prog, glm::vec3 start, glm::vec3 end)
	: Line(prog, start, end, glm::vec3(1.0f, 0.0f, 0.0f))
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

std::vector<glm::vec3> Line::setColors()
{
	std::vector<glm::vec3> colors;
	colors.push_back(color);
	colors.push_back(color);
	return colors;
}

std::vector<GLushort> Line::setIndices()
{
	std::vector<GLushort> indices;
	indices.push_back(0);
	indices.push_back(1);
	return indices;
}
