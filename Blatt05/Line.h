#pragma once
#include "VertexArrayObject.h"

/// <summary>
/// Class for rendering 1D lines
/// </summary>
/// <seealso cref="VertexArrayObject" />
class Line :
	public VertexArrayObject
{
public:
	Line(cg::GLSLProgram& prog, glm::vec3 start, glm::vec3 end);
	~Line();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors(const glm::vec3& color);
	std::vector<GLuint> setIndices();

private:
	glm::vec3 start;
	glm::vec3 end;
};

