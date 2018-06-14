#include "SolidSphere.h"

const double SolidSphere::defaultRadius(1.0);

//const glm::vec3 SolidSphere::defaultColor(1.0f, 0.0f, 0.0f); // Does not work for some reason

SolidSphere::SolidSphere(
							cg::GLSLProgram & prog,
							double radius,
							unsigned int stacks,
							unsigned int slices,
							bool lighting
						)
	: VertexArrayObject(prog, lighting, SolidSphere::primitive),
	radius(radius),
	nStacks(stacks),
	nSlices(slices)
{
}

SolidSphere::SolidSphere(cg::GLSLProgram & prog, double radius, bool lighting)
	: VertexArrayObject(prog, lighting, SolidSphere::primitive),
	radius(radius),
	nStacks(SolidSphere::nStacksDefault),
	nSlices(SolidSphere::nSlicesDefault)
{
}

SolidSphere::SolidSphere(cg::GLSLProgram & prog, bool lighting)
	: VertexArrayObject(prog, lighting, SolidSphere::primitive),
	radius(SolidSphere::defaultRadius),
	nStacks(SolidSphere::nStacksDefault),
	nSlices(SolidSphere::nSlicesDefault)
{
}

SolidSphere::SolidSphere(cg::GLSLProgram & prog)
	: VertexArrayObject(prog, SolidSphere::defaultLighting, SolidSphere::primitive),
	radius(SolidSphere::defaultRadius),
	nStacks(SolidSphere::nStacksDefault),
	nSlices(SolidSphere::nSlicesDefault)
{
}

SolidSphere::~SolidSphere()
{
}

std::vector<glm::vec3> SolidSphere::setVertices()
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

std::vector<glm::vec3> SolidSphere::setColors(const glm::vec3 & color)
{
	std::vector<glm::vec3> colors;
	for (int i = 0; i <= nStacks; ++i) {
		// Loop Through Slices
		for (int j = 0; j <= nSlices; ++j) {
			colors.push_back(color);
		}
	}
	return colors;
}

std::vector<glm::vec3> SolidSphere::setNormals()
{
	std::vector<glm::vec3> normals;
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
			normals.push_back(glm::normalize(glm::vec3(x, y, z)));
		}
	}
	return normals;
}

std::vector<GLuint> SolidSphere::setIndices()
{
	std::vector<GLuint> indices;
	for (int i = 0; i < nSlices * nStacks + nSlices; ++i) {

		indices.push_back(i);
		indices.push_back(i + nSlices + 1);
		indices.push_back(i + nSlices);

		indices.push_back(i + nSlices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	return indices;
}