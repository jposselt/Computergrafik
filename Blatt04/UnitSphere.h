#pragma once
#include "GLSLProgram.h"

class UnitSphere
{
public:
	UnitSphere(cg::GLSLProgram &program);
	~UnitSphere();
	void init();
	void draw(glm::mat4x4 mvp);
private:
	/*  */
	cg::GLSLProgram &prog;
	/* IDs for several buffers. */
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
	/* Model matrix */
	//glm::mat4x4 model;
	/* Constants */
	const double radius = 1.0;
	const int stacks = 15;
	const int slices = 15;
};