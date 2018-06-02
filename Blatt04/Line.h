#pragma once
#include "VertexArrayObject.h"
class Line :
	public VertexArrayObject
{
public:
	Line(cg::GLSLProgram *prog, glm::vec3 start, glm::vec3 end, glm::vec3 color);
	Line(cg::GLSLProgram *prog, glm::vec3 start, glm::vec3 end);
	~Line();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors();
	std::vector<GLushort> setIndices();

private:
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 color;
};

