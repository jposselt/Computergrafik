#pragma once

#include "GLSLProgram.h"
#include "TextureObject.h"

class VertexArrayObject
{
public:
	VertexArrayObject(cg::GLSLProgram& shader, bool useLighting, GLenum mode);
	VertexArrayObject(cg::GLSLProgram& shader);
	~VertexArrayObject();

	void init(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& colors, std::vector<glm::vec2>& texCoords, std::vector<GLuint>& indices);
	void init(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, glm::vec3& color, std::vector<glm::vec2>& texCoords, std::vector<GLuint>& indices);
	void render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection);

	void useLighting(bool lighting);
	void useTexture(bool value);
	void setMode(GLenum mode);
	void setShader(cg::GLSLProgram& shader);
	void setMaterial(glm::vec3 material, float shininess);
	void setVertices(std::vector<glm::vec3> vertices);
	void setColors(std::vector<glm::vec3> colors);
	void setUniColor(glm::vec3 color);
	void setNormals(std::vector<glm::vec3> normals);
	void setTexCoords(std::vector<glm::vec2> texCoords);
	void setIndices(std::vector<GLuint> indices);
	void setTexture(std::string texFile);
	GLint getVertexCount();

protected:
	/* Shader program */
	cg::GLSLProgram program;

	TextureObject textureObj;

private:
	void createAndBindBuffer(GLuint& buffer, const char* name, glm::vec3* data, size_t size);
	void createAndBindBuffer(GLuint& buffer, const char* name, glm::vec2* data, size_t size);

	/* IDs for several buffers. */
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;

	/* Number of indices */
	GLuint indexCount;

	/* Number of vertices */
	GLuint vertexCount;

	/* Object uses lighting */
	bool lighting;

	/* Object uses texture */
	bool texture;

	/* Material properties */
	glm::vec3 material;
	float shininess;

	/* Primitives to render */
	GLenum mode;
};

