#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

#include "Mesh.h"
#include "ObjParser.h"
#include "MeshAnalyser.h"
#include "VertexArrayObject.h"

// Standard window width
const int WINDOW_WIDTH = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram simple;
cg::GLSLProgram flat;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

glm::vec3 eye(0.0f, 0.0f, 5.0f);
glm::vec3 center(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);

const char* objFile = "A4_testcube2_mitSpitze.obj";
Mesh mesh;
ObjParser parser;
VertexArrayObject *vao;

/*
Initialization. Should return true if everything is ok and false if something went wrong.
*/
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Create a shader program and set light direction.
	if (!simple.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << simple.log();
		return false;
	}

	if (!simple.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT))
	{
		std::cerr << simple.log();
		return false;
	}

	if (!simple.link())
	{
		std::cerr << simple.log();
		return false;
	}

	view = glm::lookAt(eye, center, up);

	vao = new VertexArrayObject(simple, false, GL_TRIANGLES);
	vao->setVertices( { { 0.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 0.0f } });
	vao->setUniColor( { 1.0f, 1.0f, 1.0f }, 3);
	vao->setIndices({0,1,2});

	return true;
}

/*
Release resources on termination.
*/
void release()
{
}

/*
Rendering.
*/
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vao->render({projection*view, glm::mat4x4(1.0f), glm::mat3x3(1.0f) });
}

void glutDisplay()
{
	GLCODE(render());
	glutSwapBuffers();
}

/*
Resize callback.
*/
void glutResize(int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float)width / height, zNear, zFar);
}

/*
Callback for char input.
*/
void glutKeyboard(unsigned char keycode, int x, int y)
{
	static bool positionLightNext = true;
	static float zoomFactor = 1.0;
	static float zoomStep = 0.1;
	static float minZoom = 0.4;
	static float maxZoom = 3.0;

	switch (keycode)
	{
	case 27: // ESC
		glutDestroyWindow(glutID);
		return;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	parser.loadMesh(objFile, mesh);
	mesh.calculateNormals();
	MeshAnalyser::analyse(mesh);

	// GLUT: Initialize freeglut library (window toolkit).
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.0 core profile).
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("Aufgabenblatt 06");
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
	//glutIdleFunc(glutDisplay); // redisplay when idle

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
	glutMainLoop();

	// Clean up everything on termination.
	release();

	return 0;
}
