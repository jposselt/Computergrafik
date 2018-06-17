#pragma once
#include "VertexArrayObject.h"
class Cube :
	public VertexArrayObject
{
public:
	Cube(cg::GLSLProgram & prog);
	Cube(cg::GLSLProgram & prog, bool lighting);

	~Cube();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors(const glm::vec3& color);
	std::vector<glm::vec3> setNormals();
	std::vector<GLuint> setIndices();

private:
	static const GLenum primitive = GL_TRIANGLES;
};

