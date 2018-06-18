#include "SolidSphere.h"

/// <summary>
/// The default radius of the sphere
/// </summary>
const double SolidSphere::defaultRadius(1.0);

/// <summary>
/// Initializes a new instance of the <see cref="SolidSphere"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="radius">The radius of the sphere.</param>
/// <param name="stacks">The number of vertical divisions to approximate a sphere.</param>
/// <param name="slices">The number of horizontal divisions to approximate a sphere.</param>
/// <param name="lighting">If set to <c>true</c> surface normals and material properties are passed to the shader.</param>
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

/// <summary>
/// Initializes a new instance of the <see cref="SolidSphere"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="radius">The radius of the sphere.</param>
/// <param name="lighting">If set to <c>true</c> surface normals and material properties are passed to the shader.</param>
SolidSphere::SolidSphere(cg::GLSLProgram & prog, double radius, bool lighting)
	: VertexArrayObject(prog, lighting, SolidSphere::primitive),
	radius(radius),
	nStacks(SolidSphere::nStacksDefault),
	nSlices(SolidSphere::nSlicesDefault)
{
}

/// <summary>
/// Initializes a new instance of the <see cref="SolidSphere"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="lighting">If set to <c>true</c> surface normals and material properties are passed to the shader.</param>
SolidSphere::SolidSphere(cg::GLSLProgram & prog, bool lighting)
	: VertexArrayObject(prog, lighting, SolidSphere::primitive),
	radius(SolidSphere::defaultRadius),
	nStacks(SolidSphere::nStacksDefault),
	nSlices(SolidSphere::nSlicesDefault)
{
}

/// <summary>
/// Initializes a new instance of the <see cref="SolidSphere"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
SolidSphere::SolidSphere(cg::GLSLProgram & prog)
	: VertexArrayObject(prog, SolidSphere::defaultLighting, SolidSphere::primitive),
	radius(SolidSphere::defaultRadius),
	nStacks(SolidSphere::nStacksDefault),
	nSlices(SolidSphere::nSlicesDefault)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="SolidSphere"/> class.
/// </summary>
SolidSphere::~SolidSphere()
{
}

/// <summary>
/// Sets the vertices.
/// </summary>
/// <returns></returns>
std::vector<glm::vec3> SolidSphere::setVertices()
{
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
	return vertices;
}

/// <summary>
/// Sets the colors.
/// </summary>
/// <param name="color">The color.</param>
/// <returns></returns>
std::vector<glm::vec3> SolidSphere::setColors(const glm::vec3 & color)
{
	std::vector<glm::vec3> colors;
	for (unsigned int i = 0; i <= nStacks; ++i) {
		// Loop Through Slices
		for (unsigned int j = 0; j <= nSlices; ++j) {
			colors.push_back(color);
		}
	}
	return colors;
}

/// <summary>Set the surface normals.</summary>
/// <returns>Vector of surface normal vectors for each vertex</returns>
std::vector<glm::vec3> SolidSphere::setNormals()
{
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
	return normals;
}

/// <summary>
/// Sets the order in which vertices are rendered.
/// </summary>
/// <returns></returns>
std::vector<GLuint> SolidSphere::setIndices()
{
	std::vector<GLuint> indices;
	for (unsigned int i = 0; i < nSlices * nStacks + nSlices; ++i) {

		indices.push_back(i);
		indices.push_back(i + nSlices + 1);
		indices.push_back(i + nSlices);
		
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + nSlices + 1);
	}
	return indices;
}