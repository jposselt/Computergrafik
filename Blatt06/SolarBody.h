#pragma once
#include <glm/glm.hpp>
#include "GeometryObject.h"

class SolarBody
{
public:
	SolarBody(GeometryObject* model, GeometryObject* axis, GeometryObject* orbit, double orbitSpeed, double rotationSpeed, double axisTilt, double yOffset, double startAngle);
	~SolarBody();

	void render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection, double time);
	void addSatellite(SolarBody *satellite);
	//void rotateX();
	//void rotateY();
	//void rotateZ();

	/* Adjust Parameters */
	void increaseAxisTilt(double value);
	void decreaseAxisTilt(double value);
	void increaseYOffset(double value);
	void decreaseYOffset(double value);
	void drawAxis(bool value);
	void drawOrbit(bool value);

private:
	/* Parameters */
	double distance;
	double orbitSpeed;
	double rotationSpeed;
	double axisTilt;
	double yOffset;

	/* Instance Variables */
	float currentOrbitAngle;
	float currentRotationAngle;

	/* Draw Options */
	bool axis;
	bool orbit;

	/* Lock orientation to trajectory */
	//bool trajectory;

	/* Drawable Objects */
	GeometryObject *objectModel, *objectAxis, *objectOrbit;

	/* List of Satellite Objects */
	std::vector<SolarBody*> satellites;
};

