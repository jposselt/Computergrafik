#pragma once
#include "WireSphere.h"
#include "Circle.h"
#include "Line.h"

class CelestialObject
{
public:
	CelestialObject(cg::GLSLProgram *prog, double distance, double radius, double orbitSpeed, double rotationSpeed, glm::vec3 color, double axisTilt, double yOffset);
	~CelestialObject();
	void init();
	void draw(glm::mat4x4 mvp, double time);
	void addSatellite(CelestialObject *satellite);

	/* Adjust Parameters */
	void increaseAxisTilt(double value);
	void decreaseAxisTilt(double value);
	void increaseYOffset(double value);
	void decreaseYOffset(double value);
	void drawAxis(bool value);
	void drawOrbit(bool value);

protected:
	/* Program reference */
	cg::GLSLProgram *program;

private:
	/* Parameters */
	double distance;
	double radius;
	double orbitSpeed;
	double rotationSpeed;
	double axisTilt;
	double yOffset;
	glm::vec3 color;

	/* Draw Options */
	bool axis;
	bool orbit;

	/* Drawable Objects */
	VertexArrayObject *objectModel, *objectAxis, *objectOrbit;
	
	/* List of Satellite Objects */
	std::vector<CelestialObject*> satellites;

	/* Constants */
	const float axisScale = 3.0f;
};

