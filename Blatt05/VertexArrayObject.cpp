#include<glm\gtc\matrix_inverse.hpp>

#include "VertexArrayObject.h"

const glm::vec3 VertexArrayObject::defaultMaterial(0.7f, 0.3f, 0.0f);
const float VertexArrayObject::defaultShininess(32.0f);

VertexArrayObject::VertexArrayObject(cg::GLSLProgram& prog, bool useNormals, GLenum mode)
	: program(prog), useLighting(useNormals), mode(mode)
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

void VertexArrayObject::init(const glm::vec3 & color, const glm::vec3 & material, float shininess)
{
	// Construct sphere. These vectors can go out of scope after we have send all data to the graphics card.
	std::vector<glm::vec3> vertices = setVertices();
	std::vector<glm::vec3> colors = setColors(color);
	std::vector<glm::vec3> normals = setNormals();
	std::vector<GLuint> indices = setIndices();

	indexCount = (GLuint)indices.size();

	VertexArrayObject::material = material;
	VertexArrayObject::shininess = shininess;

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Objects with normals
	if (useLighting) {
		// Step 3: Create vertex buffer object for normal attribute and bind it to...
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

		// Bind it to normal.
		pos = glGetAttribLocation(programId, "normal");
		glEnableVertexAttribArray(pos);
		glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// Step 4: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void VertexArrayObject::init(const glm::vec3 & color)
{
	VertexArrayObject::init(color, VertexArrayObject::defaultMaterial, VertexArrayObject::defaultShininess);
}

void VertexArrayObject::render(const glm::mat4x4 & view, const glm::mat4x4 & projection, const glm::mat4x4 & model)
{
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", projection * view * model);
	if (useLighting) {
		program.setUniform("model", model);
		// Create normal matrix (nm) from model matrix.
		glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
		program.setUniform("nm", nm);

		// Set material properties
		program.setUniform("material", material);
		program.setUniform("shininess", shininess);
	}

	// Bind vertex array object so we can render the primitives.
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<glm::vec3> VertexArrayObject::setNormals()
{
	return std::vector<glm::vec3>();
}
