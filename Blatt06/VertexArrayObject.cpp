#include "VertexArrayObject.h"
#include "Constants.h"

VertexArrayObject::VertexArrayObject(cg::GLSLProgram& prog, bool useLighting, GLenum mode)
	: program(prog), lighting(useLighting), mode(mode), indexCount(0),
	material(Constants::defaultMaterial()), shininess(Constants::defaultShininess)
{
	glGenVertexArrays(1, &vao);
}

VertexArrayObject::VertexArrayObject(cg::GLSLProgram & prog)
	: VertexArrayObject(prog, false, GL_LINE)
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

void VertexArrayObject::init(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& colors, std::vector<GLuint>& indices)
{
	setVertices(vertices);
	setNormals(normals);
	setColors(colors);
	setIndices(indices);
}

void VertexArrayObject::init(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, glm::vec3& color, std::vector<GLuint>& indices)
{
	setVertices(vertices);
	setNormals(normals);
	setUniColor(color, vertices.size());
	setIndices(indices);
}

void VertexArrayObject::render(Transforms tf)
{
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", tf.mvp);
	if (lighting) {
		program.setUniform("model", tf.model);
		program.setUniform("nm", tf.nm);

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

void VertexArrayObject::useLighting(bool lighting)
{
	lighting = lighting;
}

void VertexArrayObject::setMode(GLenum mode)
{
	VertexArrayObject::mode = mode;
}

void VertexArrayObject::setShader(cg::GLSLProgram & shader)
{
	program = shader;
}

void VertexArrayObject::setMaterial(glm::vec3 material, float shininess)
{
	this->material = material;
	this->shininess = shininess;
}

void VertexArrayObject::setVertices(std::vector<glm::vec3> vertices)
{
	createAndBindBuffer(positionBuffer, "position", vertices.data(), vertices.size() * sizeof(glm::vec3));
}

void VertexArrayObject::setColors(std::vector<glm::vec3> colors)
{
	createAndBindBuffer(colorBuffer, "color", colors.data(), colors.size() * sizeof(glm::vec3));
}

void VertexArrayObject::setUniColor(glm::vec3 color, size_t size)
{
	std::vector<glm::vec3> colors(size, color);
	createAndBindBuffer(colorBuffer, "color", colors.data(), colors.size() * sizeof(glm::vec3));
}

void VertexArrayObject::setNormals(std::vector<glm::vec3> normals)
{
	createAndBindBuffer(normalBuffer, "normal", normals.data(), normals.size() * sizeof(glm::vec3));
}

void VertexArrayObject::setIndices(std::vector<GLuint> indices)
{
	glBindVertexArray(vao);

	// Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	indexCount = indices.size();
}

void VertexArrayObject::createAndBindBuffer(GLuint & buffer, const char * name, glm::vec3 * data, size_t size)
{
	GLuint programId = program.getHandle();
	GLuint pos;

	// Bind vertex array object
	glBindVertexArray(vao);

	// Create vertex buffer object
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	// Bind it
	pos = glGetAttribLocation(programId, name);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}
