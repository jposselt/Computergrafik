#include<glm\gtc\matrix_inverse.hpp>

#include "VertexArrayObject.h"

/// <summary>
/// The default material coefficients (diffuse/specular/ambient reflectivity)
/// </summary>
const glm::vec3 VertexArrayObject::defaultMaterial(0.5f, 0.5f, 0.0f);

/// <summary>
/// The default shininess
/// </summary>
const float VertexArrayObject::defaultShininess(64.0f);

/// <summary>
/// Initializes a new instance of the <see cref="VertexArrayObject"/> class.
/// </summary>
/// <param name="prog">The shader program to use for rendering.</param>
/// <param name="useLighting">If set to <c>true</c> surface normals and material properties are passed to the shader. Use <c>false</c> if representing objects with no surface (e.g. lines)</param>
/// <param name="mode">The kind of primitives to render (e.g. GL_TRIANGLES for triangles).</param>
VertexArrayObject::VertexArrayObject(cg::GLSLProgram& prog, bool useLighting, GLenum mode)
	: program(prog), useLighting(useLighting), mode(mode)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="VertexArrayObject"/> class.
/// </summary>
VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &positionBuffer);
}

/// <summary>
/// Initializes material properties of the object
/// </summary>
/// <param name="color">The object color</param>
/// <param name="material">Material coefficients for Phong lighting (diffuse/specular/ambient)</param>
/// <param name="shininess">The shininess of the material. Affects specular higlights</param>
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

/// <summary>
/// Initializes color of the object.
/// </summary>
/// <param name="color">The color.</param>
void VertexArrayObject::init(const glm::vec3 & color)
{
	VertexArrayObject::init(color, VertexArrayObject::defaultMaterial, VertexArrayObject::defaultShininess);
}

/// <summary>
/// Renders the object using the specified matrices.
/// </summary>
/// <param name="view">The view matrix.</param>
/// <param name="projection">The projection matrix.</param>
/// <param name="model">The model matrix.</param>
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

/// <summary>
/// Default implementation for setting the normals.
/// </summary>
/// <returns>Empty vector of 3-vectors</returns>
std::vector<glm::vec3> VertexArrayObject::setNormals()
{
	return std::vector<glm::vec3>();
}
