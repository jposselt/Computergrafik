#pragma once
#include "GLSLProgram.h"

class UnitSphere
{
public:
	UnitSphere(cg::GLSLProgram *prog);
	~UnitSphere();
	void init(double radius = 1.0);
	void draw(glm::mat4x4 mvp);
private:
	/* Program reference */
	cg::GLSLProgram *program;

	/* IDs for several buffers. */
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	/* Constants */
	const int stacks = 15;
	const int slices = 15;
};