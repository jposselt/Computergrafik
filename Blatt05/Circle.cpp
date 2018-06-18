#include "Circle.h"

/// <summary>
/// The default radius of the circle
/// </summary>
const double Circle::defaultRadius(1.0);

/// <summary>
/// Initializes a new instance of the <see cref="Circle"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
Circle::Circle(cg::GLSLProgram & prog)
	: Circle(prog, Circle::defaultRadius)
{
}

/// <summary>
/// Initializes a new instance of the <see cref="Circle"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="radius">The radius of the circle.</param>
Circle::Circle(cg::GLSLProgram & prog, double radius)
	: Circle(prog, radius, Circle::nEdgesDefault)
{
}

/// <summary>
/// Initializes a new instance of the <see cref="Circle"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="radius">The radius of the circle.</param>
/// <param name="edges">The number of edges to approximate a circle.</param>
Circle::Circle(cg::GLSLProgram & prog, double radius, unsigned int edges)
	: VertexArrayObject(prog, false, GL_LINES), radius(radius), nEdges(edges)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="Circle"/> class.
/// </summary>
Circle::~Circle()
{
}

/// <summary>
/// Sets the vertices.
/// </summary>
/// <returns></returns>
std::vector<glm::vec3> Circle::setVertices()
{
	std::vector<glm::vec3> vertices;
	for (unsigned int i = 0; i <= nEdges; ++i) {
		GLfloat U = i / (float)nEdges;
		GLfloat theta = U * (glm::pi <float>() * 2);
		GLfloat x = cosf(theta);
		GLfloat z = sinf(theta);
		vertices.push_back(glm::vec3(x * radius, 0.0f, z * radius));
	}
	return vertices;
}

/// <summary>
/// Sets the color.
/// </summary>
/// <param name="color">The color.</param>
/// <returns></returns>
std::vector<glm::vec3> Circle::setColors(const glm::vec3& color)
{
	std::vector<glm::vec3> colors;
	for (unsigned int i = 0; i <= nEdges; ++i) {
		colors.push_back(color);
	}
	return colors;
}

/// <summary>
/// Sets the order in which vertices are rendered.
/// </summary>
/// <returns></returns>
std::vector<GLuint> Circle::setIndices()
{
	std::vector<GLuint> indices;
	for (unsigned int i = 0; i < nEdges; ++i) {
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	return indices;
}