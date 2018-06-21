#include "VertexArrayObject.h"



VertexArrayObject::VertexArrayObject(cg::GLSLProgram& prog, bool useLighting, GLenum mode)
	: program(prog), useLighting(useLighting), mode(mode)
{
}

VertexArrayObject::VertexArrayObject(cg::GLSLProgram & prog)
	: VertexArrayObject(prog, false, GL_LINE)
{
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &positionBuffer);
}

inline void VertexArrayObject::setShader(cg::GLSLProgram & shader)
{
	program = shader;
}

inline void VertexArrayObject::setLight(LightInfo light)
{
	this->light = light;
}

inline void VertexArrayObject::setMaterial(MaterialInfo material)
{
	this->material = material;
}
