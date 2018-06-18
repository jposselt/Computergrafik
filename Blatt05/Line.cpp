#include "Line.h"

/// <summary>
/// Initializes a new instance of the <see cref="Line"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="start">Start position of the line.</param>
/// <param name="end">End position of the line.</param>
Line::Line(cg::GLSLProgram & prog, glm::vec3 start, glm::vec3 end)
	: VertexArrayObject(prog, false, GL_LINES), start(start), end(end)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="Line"/> class.
/// </summary>
Line::~Line()
{
}

/// <summary>
/// Sets the vertices.
/// </summary>
/// <returns></returns>
std::vector<glm::vec3> Line::setVertices()
{
	std::vector<glm::vec3> vertices;
	vertices.push_back(start);
	vertices.push_back(end);
	return vertices;
}

/// <summary>
/// Sets the color.
/// </summary>
/// <param name="color">The color.</param>
/// <returns></returns>
std::vector<glm::vec3> Line::setColors(const glm::vec3 & color)
{
	std::vector<glm::vec3> colors;
	colors.push_back(color);
	colors.push_back(color);
	return colors;
}

/// <summary>
/// Sets the order in which vertices are rendered.
/// </summary>
/// <returns></returns>
std::vector<GLuint> Line::setIndices()
{
	std::vector<GLuint> indices;
	indices.push_back(0);
	indices.push_back(1);
	return indices;
}
