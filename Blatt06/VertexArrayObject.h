#pragma once

#include "GLSLProgram.h"

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

	void init(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& colors, std::vector<GLuint>& indices);
	void init(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, glm::vec3& color, std::vector<GLuint>& indices);
	void render(Transforms tf);

	void useLighting(bool lighting);
	void setMode(GLenum mode);
	void setShader(cg::GLSLProgram& shader);
	void setMaterial(glm::vec3 material, float shininess);
	void setVertices(std::vector<glm::vec3> vertices);
	void setColors(std::vector<glm::vec3> colors);
	void setUniColor(glm::vec3 color);
	void setNormals(std::vector<glm::vec3> normals);
	void setIndices(std::vector<GLuint> indices);
	GLint getVertexCount();

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

	/* Number of indices */
	GLuint indexCount;

	/* Number of vertices */
	GLuint vertexCount;

	/* Object uses lighting */
	bool lighting;

	/* Material properties */
	glm::vec3 material;
	float shininess;

	/* Primitives to render */
	GLenum mode;
};

