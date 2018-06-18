#pragma once
#include "VertexArrayObject.h"

/// <summary>
/// Class for rendering solid spheres
/// </summary>
/// <seealso cref="VertexArrayObject" />
class SolidSphere :
	public VertexArrayObject
{
public:
	SolidSphere(cg::GLSLProgram & prog, double radius, unsigned int stacks, unsigned int slices, bool lighting);
	SolidSphere(cg::GLSLProgram & prog, double radius, bool lighting);
	SolidSphere(cg::GLSLProgram & prog, bool lighting);
	SolidSphere(cg::GLSLProgram & prog);
	~SolidSphere();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors(const glm::vec3& color);
	std::vector<glm::vec3> setNormals();
	std::vector<GLuint> setIndices();

private:
	double radius;
	unsigned int nStacks;
	unsigned int nSlices;

	/* Class constants */
	static const unsigned int nStacksDefault = 15;
	static const unsigned int nSlicesDefault = 15;
	static const double defaultRadius;
	static const GLenum primitive = GL_TRIANGLES;
	static const bool defaultLighting = false;
};