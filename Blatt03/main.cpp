#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

// Time of last render call in milliseconds
int lastRenderTime = 0;
// Elapsed time since last render call in milliseconds for animation
int elapsedTime = 0;

// Switches for rotation
bool rotateX = false;
bool rotateY = false;
bool rotateZ = false;

// Angular velocities for animation in degree per millisecond
float avelX = 15 / 1000.f; // 15° per second
float avelY = 15 / 1000.f; // 15° per second
float avelZ = 15 / 1000.f; // 15° per second

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;
glm::vec3 eye(4.0f, 4.0f, 4.0f);
glm::vec3 center(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);
/*
Struct to hold data for object rendering.
*/
struct Object
{
	/* IDs for several buffers. */
	GLuint vao;

	GLuint positionBuffer;
	GLuint colorBuffer;

	GLuint indexBuffer;

	/* Model matrix */
	glm::mat4x4 model;
};

Object cube;
Object axes;

void initCube()
{
	// Construct cube. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = {
		{  1.0f, -1.0f,  1.0f },{  1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f }, // Front
		{ -1.0f, -1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },{  1.0f,  1.0f, -1.0f },{  1.0f, -1.0f, -1.0f }, // Back
		{  1.0f, -1.0f, -1.0f },{  1.0f,  1.0f, -1.0f },{  1.0f,  1.0f,  1.0f },{  1.0f, -1.0f,  1.0f }, // Right
		{ -1.0f, -1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f, -1.0f },{ -1.0f, -1.0f, -1.0f }, // Left
		{  1.0f,  1.0f,  1.0f },{  1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f,  1.0f }, // Top
		{  1.0f, -1.0f, -1.0f },{  1.0f, -1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f },{ -1.0f, -1.0f, -1.0f }  // Bottom
	};
	const std::vector<glm::vec3> colors = {
		{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f }, // Front (red)
		{ 0.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f }, // Back (cyan)
		{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f }, // Right (green)
		{ 1.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 1.0f }, // Left (magenta)
		{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f }, // Top (blue)
		{ 1.0f, 1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f }  // Bottom (yellow)
	};

	const std::vector<GLushort> indices = {
		 0,  1,  2,  0,  2,  3, // Front
		 4,  5,  6,  4,  6,  7, // Back
		 8,  9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
	    16, 17, 18, 16, 18, 19, // Top
		20, 21, 22, 20, 22, 23  // Bottom
	
	};

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &cube.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cube.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &cube.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cube.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &cube.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	//cube.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
}

void initAxes()
{
	// Construct axes. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = {
		{ 0.0f, 0.0f, 0.0f },{ 2.0f, 0.0f, 0.0f }, // x-Axis
		{ 0.0f, 0.0f, 0.0f },{ 0.0f, 2.0f, 0.0f }, // y-Axis
		{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 2.0f }  // z-Axis
	};
	const std::vector<glm::vec3> colors = {
		{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f }, // x-Axis (red)
		{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f }, // y-Axis (green)
		{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f }  // z-Axis (blue)
	};

	const std::vector<GLushort> indices = {
		0,  1, // x-Axis
		2,  3, // y-Axis
		4,  5  // z-Axis
	};

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &axes.vao);
	glBindVertexArray(axes.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &axes.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axes.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &axes.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axes.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &axes.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axes.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void renderCube()
{
	// Animate model
	if (rotateX)
	{
		float angle = elapsedTime * avelX;
		glm::vec3 axis(1, 0, 0);
		glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
		cube.model = anim * cube.model;
	}

	// Create mvp.
	glm::mat4x4 mvp = projection * view * cube.model;
	

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the triangles.
	glBindVertexArray(cube.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.indexBuffer);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderAxes()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * axes.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the triangles.
	glBindVertexArray(axes.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axes.indexBuffer);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_LINES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Construct view matrix.


	view = glm::lookAt(eye, center, up);

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << program.log();
		return false;
	}

	if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT))
	{
		std::cerr << program.log();
		return false;
	}
	
	if (!program.link())
	{
		std::cerr << program.log();
		return false;
	}

	// Create objects.
	initAxes();
	initCube();

	return true;
}

/*
 Release object resources.
*/
void releaseObject(Object& obj)
{
	glDeleteVertexArrays(1, &obj.vao);
	glDeleteBuffers(1, &obj.indexBuffer);
	glDeleteBuffers(1, &obj.colorBuffer);
	glDeleteBuffers(1, &obj.positionBuffer);
}

/*
 Release resources on termination.
 */
void release()
{
	// Shader program will be released upon program termination.
	releaseObject(axes);
	releaseObject(cube);
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Calculate delta t since last render call
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - lastRenderTime;
	// Update time of last render call
	lastRenderTime = currentTime;

	renderAxes();
	renderCube();
}

void glutDisplay ()
{
   GLCODE(render());
   glutSwapBuffers();
}

/*
 Resize callback.
 */
void glutResize (int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void glutKeyboard (unsigned char keycode, int x, int y)
{
	switch (keycode)
	{
	case 27: // ESC
	  glutDestroyWindow ( glutID );
	  return;
	  
	case '+':
		
		break;
	case '-':
	
		break;
	case 'x':
		// do something
		rotateX = !rotateX;
		break;
	case 'y':
		// do something
		break;
	case 'z':
		eye = eye - (0.0f, 0.0f, 0.1f);
		view = glm::lookAt(eye, center, up);
		break;
	case 'u':
		eye = eye + (0.0f, 0.0f, 0.1f);
		view = glm::lookAt(eye, center, up);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.3 core profile).
	glutInitContextVersion(4, 0);
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("Aufgabenblatt 03");
	glutID = glutGetWindow();
	  
	// GLEW: Load opengl extensions
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	if (result != GLEW_OK) {
	   return -1;
	}

	// GLUT: Set callbacks for events.
	glutReshapeFunc(glutResize);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc   (glutDisplay); // redisplay when idle

	glutKeyboardFunc(glutKeyboard);

	// Init VAO.
	{
		GLCODE(bool result = init());
		if (!result) {
			release();
			return -2;
		}
	}

	// GLUT: Loop until the user closes the window
	// rendering & event handling
	glutMainLoop ();

	// Clean up everything on termination.
	release();

	return 0;
}
