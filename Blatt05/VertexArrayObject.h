#pragma once
#include "GLSLProgram.h"

class VertexArrayObject
{
public:
	VertexArrayObject(cg::GLSLProgram& prog, bool useLighting, GLenum mode);
	~VertexArrayObject();
	void init(const glm::vec3& color, const glm::vec3& material, float shininess);
	void init(const glm::vec3& color);
	void render(const glm::mat4x4& view, const glm::mat4x4& projection, const glm::mat4x4& model);

protected:
	/* Program reference */
	cg::GLSLProgram& program;

	/* Abstract Methods */
	virtual std::vector<glm::vec3> setVertices() = 0;
	virtual std::vector<glm::vec3> setColors(const glm::vec3& color) = 0;
	virtual std::vector<glm::vec3> setNormals();
	virtual std::vector<GLuint> setIndices() = 0;

private:
	/* IDs for several buffers. */
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;

	/* Number of Indices */
	GLuint indexCount;

	/* Material properties */
	glm::vec3 material;
	float shininess;

	/* Object uses lighting */
	bool useLighting;

	/* Primitives to render */
	GLenum mode;

	/* Class constants */
	static const glm::vec3 defaultMaterial;
	static const float defaultShininess;
};