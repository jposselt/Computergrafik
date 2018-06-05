#include <glm/gtc/matrix_transform.hpp>
#include <cmath>       /* fmod */

#include "CelestialObject.h"
#include "Constants.h"

CelestialObject::CelestialObject(cg::GLSLProgram *prog, double distance, double radius, double orbitSpeed, double rotationSpeed, glm::vec3 color, double axisTilt, double yOffset, double startAngle)
	:	program(prog),
		distance(distance),
		radius(radius),
		orbitSpeed(orbitSpeed),
		rotationSpeed(rotationSpeed),
		color(color),
		axisTilt(fmod(axisTilt, Constants::degreeCircle)),
		yOffset(yOffset),
		currentOrbitAngle(glm::radians<float>(startAngle)),
		currentRotationAngle(0.0),
		axis(true),
		orbit(true)
{
	objectModel = new WireSphere(prog, radius, color);
	objectAxis = new Line(prog, glm::vec3(0.0f, -Constants::axisScale * radius, 0.0f), glm::vec3(0.0f, Constants::axisScale * radius, 0.0f), color);
	objectOrbit = new Circle(prog, distance, color);
}


CelestialObject::~CelestialObject()
{
	delete objectModel;
	delete objectAxis;
	delete objectOrbit;

	for (CelestialObject *sat : satellites) {
		delete sat;
	}
}

void CelestialObject::init()
{
	objectModel->init();
	objectAxis->init();
	objectOrbit->init();
}

void CelestialObject::draw(glm::mat4x4 mvp, double time)
{
	/* Y-Offset */
	mvp = glm::translate(mvp, glm::vec3(0.0f, yOffset, 0.0f));

	/* Draw orbit */
	if (orbit) {
		objectOrbit->draw(mvp);
	}

	/* Translate to orbit position */
	currentOrbitAngle += glm::radians<float>(time * orbitSpeed);
	mvp = glm::translate(
		mvp,
		glm::vec3(distance * glm::cos(currentOrbitAngle), 0.0f, -distance * glm::sin(currentOrbitAngle))
	);

	/* Tilt the axis */
	mvp = glm::rotate(mvp, glm::radians<float>(axisTilt), Constants::zAxis);

	/* Draw all satelites */
	for (CelestialObject *sat : satellites) {
		sat->draw(mvp, time);
	}

	/* Draw axis */
	if (axis) {
		objectAxis->draw(mvp);
	}

	/* Rotate Object */
	currentRotationAngle += glm::radians<float>(time * rotationSpeed);
	mvp = glm::rotate(mvp, currentRotationAngle, Constants::yAxis);
	
	/* Draw the actual object */
	objectModel->draw(mvp);
}

void CelestialObject::addSatellite(CelestialObject *satellite)
{
	satellites.push_back(satellite);
}

void CelestialObject::increaseAxisTilt(double value)
{
	if (axisTilt < Constants::maxTilt) {
		axisTilt += value;
	}
}

void CelestialObject::decreaseAxisTilt(double value)
{
	if (axisTilt > Constants::minTilt) {
		axisTilt -= value;
	}
}

void CelestialObject::increaseYOffset(double value)
{
	yOffset += value;
}

void CelestialObject::decreaseYOffset(double value)
{
	yOffset -= value;
}

void CelestialObject::drawAxis(bool value)
{
	axis = value;
}

void CelestialObject::drawOrbit(bool value)
{
	orbit = value;
}
