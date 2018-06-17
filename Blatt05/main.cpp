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

#include "ShadedPlanets.h"

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram simple;
cg::GLSLProgram flat;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;
glm::vec3 eye(0.0f, 0.0f, 30.0f);
glm::vec3 center(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);

// Planetary System
//SolarBody *planet = new SolarBody(simple, flat, 0.0, 1.0, 0.0, 0.0, glm::vec3(1.0f,1.0f,0.0f), 0.0, 0.0, 0.0);
ShadedPlanets *planets = new ShadedPlanets();


/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	/*
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Construct view matrix.
	view = glm::lookAt(eye, center, up);

	// Create shader program with no lighting.
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

	// Create a shader program with flat lighting.
	if (!flat.compileShaderFromFile("shader/flat.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << flat.log();
		return false;
	}

	if (!flat.compileShaderFromFile("shader/flat.frag", cg::GLSLShader::FRAGMENT))
	{
		std::cerr << flat.log();
		return false;
	}

	if (!flat.link())
	{
		std::cerr << flat.log();
		return false;
	}

	// Set light position/direction
	flat.use();
	//flat.setUniform("lightPosition", glm::normalize(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)));
	flat.setUniform("lightPosition", glm::vec4(eye, 1.0f));
	flat.setUniform("directLight", glm::vec3(1.0));  // white light
	flat.setUniform("ambientLight", glm::vec3(0.0)); // no ambient light

	// Set camera position
	flat.setUniform("cameraPosition", eye);

	// Initialize planetary system
	planet->init();
	*/
	view = glm::lookAt(eye, center, up);
	planets->init();

	return true;
}

/*
 Release resources on termination.
 */
void release()
{
	// Shader program will be released upon program termination.
	delete planets;
}

/*
 Rendering.
 */
void render()
{
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glDepthFunc(GL_LEQUAL);

	// Draw the planetary system
	planets->render(glm::mat4(1.0), view, projection);
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
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.0 core profile).
	glutInitContextVersion(4, 0);
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("Aufgabenblatt 05");
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
