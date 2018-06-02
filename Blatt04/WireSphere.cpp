#include "WireSphere.h"


WireSphere::WireSphere(cg::GLSLProgram *prog, double radius, glm::vec3 color, unsigned int stacks, unsigned int slices)
	: VertexArrayObject(prog), radius(radius), color(color), nStacks(stacks), nSlices(slices)
{
}

WireSphere::WireSphere(cg::GLSLProgram * prog, double radius, glm::vec3 color)
	: WireSphere(prog, radius, color, 15, 15)
{
}


WireSphere::WireSphere(cg::GLSLProgram * prog)
	: WireSphere(prog, 1.0, glm::vec3(1.0f, 0.0f, 0.0f), 15 ,15)
{
}


WireSphere::~WireSphere()
{
}

std::vector<glm::vec3> WireSphere::setVertices()
{
	std::vector<glm::vec3> vertices;
	for (int i = 0; i <= nStacks; ++i) {

		GLfloat V = i / (float)nStacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= nSlices; ++j) {

			GLfloat U = j / (float)nSlices;
			GLfloat theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(glm::vec3(x * radius, y * radius, z * radius));
		}
	}
	return vertices;
}

std::vector<glm::vec3> WireSphere::setColors()
{
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> vertices;
	for (int i = 0; i <= nStacks; ++i) {
		// Loop Through Slices
		for (int j = 0; j <= nSlices; ++j) {
			colors.push_back(color);
		}
	}
	return colors;
}

std::vector<GLushort> WireSphere::setIndices()
{
	std::vector<GLushort> indices;
	for (int i = 0; i < nSlices * nStacks + nSlices; ++i) {

		indices.push_back(i);
		indices.push_back(i + nSlices + 1);
		indices.push_back(i + nSlices);
		indices.push_back(i + nSlices + 1);
	}
	return indices;
}
