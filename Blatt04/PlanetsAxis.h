#pragma once
#include "GLSLProgram.h"

class PlanetsAxis
{
public:
	PlanetsAxis(cg::GLSLProgram *prog);
	~PlanetsAxis();
	void init();
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
	const float yStart = -2.0f;
	const float yEnd   =  2.0f;
};

