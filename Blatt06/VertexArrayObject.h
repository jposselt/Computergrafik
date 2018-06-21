#pragma once

#include "GLSLProgram.h"
#include "LightInfo.h"
#include "MaterialInfo.h"

class VertexArrayObject
{
public:
	VertexArrayObject(cg::GLSLProgram& shader, bool useLighting, GLenum mode);
	VertexArrayObject(cg::GLSLProgram& shader);
	~VertexArrayObject();

	//void render(const glm::mat4x4& view, const glm::mat4x4& projection, const glm::mat4x4& model);

	void setShader(cg::GLSLProgram& shader);
	void setLight(LightInfo light);
	void setMaterial(MaterialInfo material);

	//void setVertices(std::vector<glm::vec3> vertices);
	//void setColors(std::vector<glm::vec3> colors);
	//void setUniColor(glm::vec3 color);
	//void setNormals(std::vector<glm::vec3> normals);
	//void setIndices(std::vector<GLuint> indices);

protected:
	/* Program reference */
	cg::GLSLProgram& program;

private:
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

