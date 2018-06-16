#include "FlatSphere.h"

const double FlatSphere::defaultRadius(1.0);

FlatSphere::FlatSphere(
	cg::GLSLProgram & prog,
	double radius,
	unsigned int stacks,
	unsigned int slices,
	bool lighting
)
	: VertexArrayObject(prog, lighting, FlatSphere::primitive),
	radius(radius),
	nStacks(stacks),
	nSlices(slices)
{
}

FlatSphere::FlatSphere(cg::GLSLProgram & prog, double radius, bool lighting)
	: VertexArrayObject(prog, lighting, FlatSphere::primitive),
	radius(radius),
	nStacks(FlatSphere::nStacksDefault),
	nSlices(FlatSphere::nSlicesDefault)
{
}

FlatSphere::FlatSphere(cg::GLSLProgram & prog, bool lighting)
	: VertexArrayObject(prog, lighting, FlatSphere::primitive),
	radius(FlatSphere::defaultRadius),
	nStacks(FlatSphere::nStacksDefault),
	nSlices(FlatSphere::nSlicesDefault)
{
}

FlatSphere::FlatSphere(cg::GLSLProgram & prog)
	: VertexArrayObject(prog, FlatSphere::defaultLighting, FlatSphere::primitive),
	radius(FlatSphere::defaultRadius),
	nStacks(FlatSphere::nStacksDefault),
	nSlices(FlatSphere::nSlicesDefault)
{
}

FlatSphere::~FlatSphere()
{
}

std::vector<glm::vec3> FlatSphere::setVertices()
{
	std::vector<glm::vec3> vertices;
	for (unsigned int i = 0; i < nStacks; ++i) {

		GLfloat V0 = i / (float)nStacks;
		GLfloat V1 = (i+1) / (float)nStacks;
		GLfloat phi0 = V0 * glm::pi <float>();
		GLfloat phi1 = V1 * glm::pi <float>();

		// Loop Through Slices
		for (unsigned int j = 0; j <= nSlices; ++j) {

			GLfloat U0 = j / (float)nSlices;
			GLfloat U1 = (j+1) / (float)nSlices;
			GLfloat theta0 = U0 * (glm::pi <float>() * 2);
			GLfloat theta1 = U1 * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x00 = cosf(theta0) * sinf(phi0);
			GLfloat x01 = cosf(theta1) * sinf(phi0);
			GLfloat x11 = cosf(theta1) * sinf(phi1);
			GLfloat x10 = cosf(theta0) * sinf(phi1);
			
			GLfloat y0 = cosf(phi0);
			GLfloat y1 = cosf(phi1);

			GLfloat z00 = sinf(theta0) * sinf(phi0);
			GLfloat z01 = sinf(theta1) * sinf(phi0);
			GLfloat z11 = sinf(theta1) * sinf(phi1);
			GLfloat z10 = sinf(theta0) * sinf(phi1);

			// Push Back Vertex Data
			vertices.push_back(glm::vec3(x00 * radius, y0 * radius, z00 * radius));
			vertices.push_back(glm::vec3(x01 * radius, y0 * radius, z01 * radius));
			vertices.push_back(glm::vec3(x11 * radius, y1 * radius, z11 * radius));
			vertices.push_back(glm::vec3(x10 * radius, y1 * radius, z10 * radius));
		}
	}
	return vertices;
}

std::vector<glm::vec3> FlatSphere::setColors(const glm::vec3 & color)
{
	std::vector<glm::vec3> colors;
	for (unsigned int i = 0; i < nStacks; ++i) {
		// Loop Through Slices
		for (unsigned int j = 0; j <= nSlices; ++j) {
			colors.push_back(color);
			colors.push_back(color);
			colors.push_back(color);
			colors.push_back(color);
		}
	}
	return colors;
}

std::vector<glm::vec3> FlatSphere::setNormals()
{
	std::vector<glm::vec3> normals;
	for (unsigned int i = 0; i < nStacks; ++i) {

		GLfloat V0 = i / (float)nStacks;
		GLfloat V1 = (i + 1) / (float)nStacks;
		GLfloat phi0 = V0 * glm::pi <float>();
		GLfloat phi1 = V1 * glm::pi <float>();

		// Loop Through Slices
		for (unsigned int j = 0; j <= nSlices; ++j) {

			GLfloat U0 = j / (float)nSlices;
			GLfloat U1 = (j + 1) / (float)nSlices;
			GLfloat theta0 = U0 * (glm::pi <float>() * 2);
			GLfloat theta1 = U1 * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x00 = cosf(theta0) * sinf(phi0);
			GLfloat x01 = cosf(theta1) * sinf(phi0);
			GLfloat x11 = cosf(theta1) * sinf(phi1);
			GLfloat x10 = cosf(theta0) * sinf(phi1);

			GLfloat y0 = cosf(phi0);
			GLfloat y1 = cosf(phi1);

			GLfloat z00 = sinf(theta0) * sinf(phi0);
			GLfloat z01 = sinf(theta1) * sinf(phi0);
			GLfloat z11 = sinf(theta1) * sinf(phi1);
			GLfloat z10 = sinf(theta0) * sinf(phi1);

			GLfloat x_avg = (x00 + x01 + x10 + x11)/4;
			GLfloat y_avg = (y0 + y1)/2;
			GLfloat z_avg = (z00 + z01 + z10 + z11) / 4;

			// Push Back Vertex Data
			normals.push_back(normalize(glm::vec3(x_avg, y_avg, z_avg)));
			normals.push_back(normalize(glm::vec3(x_avg, y_avg, z_avg)));
			normals.push_back(normalize(glm::vec3(x_avg, y_avg, z_avg)));
			normals.push_back(normalize(glm::vec3(x_avg, y_avg, z_avg)));
		}
	}
	return normals;
}

std::vector<GLuint> FlatSphere::setIndices()
{
	std::vector<GLuint> indices;
	for (unsigned int i = 0; i < 4 *(nStacks * nSlices + nSlices); i += 4) {

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 2);
		indices.push_back(i + 3);
		indices.push_back(i);
	}
	return indices;
}