#pragma once
#include "GLSLProgram.h"

class VertexArrayObject
{
public:
	VertexArrayObject(cg::GLSLProgram *prog);
	~VertexArrayObject();
	void init();
	void draw(glm::mat4x4 mvp);

protected:
	/* Program reference */
	cg::GLSLProgram *program;

	/* Abstract Methods */
	virtual std::vector<glm::vec3> setVertices() = 0;
	virtual std::vector<glm::vec3> setColors() = 0;
	virtual std::vector<GLushort> setIndices() = 0;

private:
	/* IDs for several buffers. */
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
};

