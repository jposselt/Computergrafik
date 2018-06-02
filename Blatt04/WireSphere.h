#pragma once
#include "VertexArrayObject.h"
class WireSphere :
	public VertexArrayObject
{
public:
	WireSphere(cg::GLSLProgram *prog, double radius, glm::vec3 color, unsigned int stacks, unsigned int slices);
	WireSphere(cg::GLSLProgram *prog, double radius, glm::vec3 color);
	WireSphere(cg::GLSLProgram *prog);
	~WireSphere();

protected:
	std::vector<glm::vec3> setVertices();
	std::vector<glm::vec3> setColors();
	std::vector<GLushort> setIndices();
	
private:
	double radius;
	glm::vec3 color;
	unsigned int nStacks;
	unsigned int nSlices;
};

