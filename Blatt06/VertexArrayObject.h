#pragma once

#include "GLSLProgram.h"
#include "LightInfo.h"
#include "MaterialInfo.h"

typedef struct {
	glm::mat4x4 mvp;    // model matrix
	glm::mat4x4 model;  // model matrix
	glm::mat3x3 nm;		// normal matrix
} Transforms;

class VertexArrayObject
{
public:
	VertexArrayObject(cg::GLSLProgram& shader, bool useLighting, GLenum mode);
	VertexArrayObject(cg::GLSLProgram& shader);
	~VertexArrayObject();

	void render(Transforms tf);

	void lighting(bool lighting);
	void setMode(GLenum mode);
	void setShader(cg::GLSLProgram& shader);
	void setLight(LightInfo light);
	void setMaterial(MaterialInfo material);
	void setVertices(std::vector<glm::vec3> vertices);
	void setColors(std::vector<glm::vec3> colors);
	void setUniColor(glm::vec3 color, size_t size);
	void setNormals(std::vector<glm::vec3> normals);
	void setIndices(std::vector<GLuint> indices);

protected:
	/* Program reference */
	cg::GLSLProgram& program;

private:
	void createAndBindBuffer(GLuint& buffer, const char* name, glm::vec3* data, size_t size);

	/* IDs for several buffers. */
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;

	/* Number of Indices */
	GLuint indexCount;

	/* Object uses lighting */
	bool useLighting;

	/* Light and Material info */
	MaterialInfo material;
	LightInfo light;

	/* Primitives to render */
	GLenum mode;
};

