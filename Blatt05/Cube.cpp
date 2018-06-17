#include "Cube.h"

Cube::Cube(cg::GLSLProgram & prog)
	: Cube(prog, false)
{
}

Cube::Cube(cg::GLSLProgram & prog, bool lighting)
	: VertexArrayObject(prog, lighting, Cube::primitive)
{
}

Cube::~Cube()
{
}

std::vector<glm::vec3> Cube::setVertices()
{
	std::vector<glm::vec3> vertices = {
		{ 1.0f, -1.0f,  1.0f },{ 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f }, // Front
		{ -1.0f, -1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f }, // Back
		{ 1.0f, -1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f }, // Right
		{ -1.0f, -1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f, -1.0f },{ -1.0f, -1.0f, -1.0f }, // Left
		{ 1.0f,  1.0f,  1.0f },{ 1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f,  1.0f }, // Top
		{ 1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f },{ -1.0f, -1.0f, -1.0f }  // Bottom
	};
	return vertices;
}

std::vector<glm::vec3> Cube::setColors(const glm::vec3 & color)
{
	std::vector<glm::vec3> colors = {
		color, color, color, color,
		color, color, color, color,
		color, color, color, color,
		color, color, color, color,
		color, color, color, color,
		color, color, color, color
	};
	return colors;
}

std::vector<glm::vec3> Cube::setNormals()
{
	std::vector<glm::vec3> normals = {
		{ 0.0f, 0.0f,  1.0f }, { 0.0f,  0.0f,  1.0f }, { 0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f,  1.0f }, // Front
		{ 0.0f, 0.0f, -1.0f }, { 0.0f,  0.0f, -1.0f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, // Back

		{  1.0f, 0.0f, 0.0f }, {  1.0f, 0.0f, 0.0f }, {  1.0f, 0.0f, 0.0f }, {  1.0f, 0.0f, 0.0f }, // Right
		{ -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, // Left

		{ 0.0f,  1.0f, 0.0f }, { 0.0f,  1.0f, 0.0f }, { 0.0f,  1.0f, 0.0f }, { 0.0f,  1.0f, 0.0f }, // Top
		{ 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }  // Bottom
	};
	return normals;
}

std::vector<GLuint> Cube::setIndices()
{
	std::vector<GLuint> indices = {
		0,  1,  2,  0,  2,  3, // Front
		4,  5,  6,  4,  6,  7, // Back
		8,  9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Top
		20, 21, 22, 20, 22, 23  // Bottom

	};
	return indices;
}
