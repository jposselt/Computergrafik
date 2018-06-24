#include "Sphere.h"
#include "Constants.h"

Sphere::Sphere(cg::GLSLProgram & shader, double radius, unsigned int stacks, unsigned int slices, bool lighting)
	: GeometryObject(nullptr, nullptr, nullptr, nullptr), radius(radius), nStacks(stacks), nSlices(slices)
{
	VertexArrayObject* geometry = new VertexArrayObject(shader, lighting, GL_TRIANGLES);

	// Vertices
	std::vector<glm::vec3> vertices;
	for (unsigned int i = 0; i <= nStacks; ++i) {

		GLfloat V = i / (float)nStacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (unsigned int j = 0; j <= nSlices; ++j) {

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
	geometry->setVertices(vertices);

	// Normals
	std::vector<glm::vec3> normals;
	for (unsigned int i = 0; i <= nStacks; ++i) {

		GLfloat V = i / (float)nStacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (unsigned int j = 0; j <= nSlices; ++j) {

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
	geometry->setNormals(normals);

	// Indices
	std::vector<GLuint> indices;
	for (unsigned int i = 0; i < nSlices * nStacks + nSlices; ++i) {

		indices.push_back(i);
		indices.push_back(i + nSlices + 1);
		indices.push_back(i + nSlices);

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + nSlices + 1);
	}
	geometry->setIndices(indices);

	this->setGeometry(geometry);
	this->setGeometryColor(Constants::defaultColor());
}

Sphere::~Sphere()
{

}
