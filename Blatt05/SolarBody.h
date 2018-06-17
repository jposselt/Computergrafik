#pragma once
#include "Line.h"
#include "Circle.h"
#include "SolidSphere.h"
#include "FlatSphere.h"
#include "Cube.h"

class SolarBody
{
public:
	SolarBody(cg::GLSLProgram & simple, cg::GLSLProgram & lighting, double distance, double radius, double orbitSpeed, double rotationSpeed, glm::vec3 color, double axisTilt, double yOffset, double startAngle);
	~SolarBody();
	void init();
	void render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection, double time);
	void addSatellite(SolarBody *satellite);

	/* Adjust Parameters */
	void increaseAxisTilt(double value);
	void decreaseAxisTilt(double value);
	void increaseYOffset(double value);
	void decreaseYOffset(double value);
	void drawAxis(bool value);
	void drawOrbit(bool value);

protected:
	/* Program references */
	cg::GLSLProgram & simpleShader;   // Shader for 1D objects (no lighting)
	cg::GLSLProgram & lightingShader; // Shader for objects with lighting

private:
	/* Parameters */
	double distance;
	double radius;
	double orbitSpeed;
	double rotationSpeed;
	double axisTilt;
	double yOffset;
	glm::vec3 color;

	/* Instance Variables */
	float currentOrbitAngle;
	float currentRotationAngle;

	/* Draw Options */
	bool axis;
	bool orbit;

	/* Drawable Objects */
	VertexArrayObject *objectModel, *objectAxis, *objectOrbit;

	/* List of Satellite Objects */
	std::vector<SolarBody*> satellites;
};

