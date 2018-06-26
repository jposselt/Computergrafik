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
#include "Constants.h"

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
glm::vec3 eye = Constants::eye();

// Planetary System
ShadedPlanets *planets = new ShadedPlanets();


/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	view = glm::lookAt(eye, Constants::center(), Constants::up());
	planets->init();
	planets->setCamera(eye);
	planets->setLight(Constants::lightDirection(), Constants::directLight(), Constants::ambientLight());

	return true;
}

/*
 Release resources on termination.
 */
void release()
{
	delete planets;
}

/*
 Rendering.
 */
void render()
{
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
	static bool vertexNormals = false;
	static bool faceNormals = false;
	static bool boundingBox = false;
	static bool positionLightNext = true;
	static float zoomFactor = Constants::initialZoomFactor;
	static float scale = Constants::initialObjectScale;

	switch (keycode)
	{
	case 27: // ESC
	  glutDestroyWindow ( glutID );
	  return;
	case '1':
		if (positionLightNext) {
			planets->setLight(glm::vec4(eye, 1.0), Constants::directLight(), Constants::ambientLight());
			planets->setCamera(eye);
		} 
		else {
			planets->setLight(Constants::lightDirection(), Constants::directLight(), Constants::ambientLight());
			planets->setCamera(eye);
		}
		positionLightNext = !positionLightNext;
		break;
	case '2':
		planets->switchShader();
		break;
	case 'b':
		boundingBox = !boundingBox;
		planets->showBoundingBox(boundingBox);
		break;
	case 'n':
		vertexNormals = !vertexNormals;
		planets->showVertexNormals(vertexNormals);
		break;
	case 'h':
		faceNormals = !faceNormals;
		planets->showFaceNormals(faceNormals);
		break;
	case 's':
		if (scale > Constants::minSacling) {
			scale -= Constants::scalingStep;
			planets->scale(scale);
		}
		break;
	case 'S':
		if (scale < Constants::maxScaling) {
			scale += Constants::scalingStep;
			planets->scale(scale);
		}
		break;
	case 'x':
		planets->rotateX(Constants::manualRotationStep);
		break;
	case 'X':
		planets->rotateX(-Constants::manualRotationStep);
		break;
	case 'y':
		planets->rotateY(Constants::manualRotationStep);
		break;
	case 'Y':
		planets->rotateY(-Constants::manualRotationStep);
		break;
	case 'z':
		planets->rotateZ(Constants::manualRotationStep);
		break;
	case 'Z':
		planets->rotateZ(-Constants::manualRotationStep);
		break;
	case '+':
		if (zoomFactor > Constants::minZoom) {
			zoomFactor -= Constants::zoomStep;
			eye = zoomFactor * Constants::eye();
			view = glm::lookAt(eye, Constants::center(), Constants::up());
			if (!positionLightNext) {
				planets->setLight(glm::vec4(eye, 1.0), Constants::directLight(), Constants::ambientLight());
			}
			planets->setCamera(eye);
		}
		break;
	case '-':
		if (zoomFactor < Constants::maxZoom) {
			zoomFactor += Constants::zoomStep;
			eye = zoomFactor * Constants::eye();
			view = glm::lookAt(eye, Constants::center(), Constants::up());
			if (!positionLightNext) {
				planets->setLight(glm::vec4(eye, 1.0), Constants::directLight(), Constants::ambientLight());
			}
			planets->setCamera(eye);
		}
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

	// GLUT: Create a window and opengl context (version 4.0 core profile).
	glutInitContextVersion(4, 0);
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

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
