#include <glm/gtc/matrix_transform.hpp>
#include <cmath>       /* fmod */

#include "SolarBody.h"
#include "Constants.h"

SolarBody::SolarBody(
	cg::GLSLProgram & simple,
	cg::GLSLProgram & lighting,
	double distance,
	double radius,
	double orbitSpeed,
	double rotationSpeed,
	glm::vec3 color,
	double axisTilt,
	double yOffset,
	double startAngle
) 
	: simpleShader(simple),
	lightingShader(lighting),
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
	objectModel = new SolidSphere(lightingShader, radius, Constants::stacks, Constants::slices, true);
	//objectModel = new Cube(lightingShader, true);
	objectAxis = new Line(simpleShader, -Constants::axisScale * (float)radius * Constants::yAxis(), Constants::axisScale * (float)radius * Constants::yAxis());
	objectOrbit = new Circle(simpleShader, distance);
}

SolarBody::~SolarBody()
{
	delete objectModel;
	delete objectAxis;
	delete objectOrbit;

	for (SolarBody *sat : satellites) {
		delete sat;
	}
}

void SolarBody::init()
{
	objectModel->init(color);
	objectAxis->init(color);
	objectOrbit->init(color);
}

void SolarBody::render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection, double time)
{
	/* Y-Offset */
	model = glm::translate(model, glm::vec3(0.0f, yOffset, 0.0f));

	/* Draw orbit */
	if (orbit) {
		objectOrbit->render(view, projection, model);
	}

	/* Translate to orbit position */
	currentOrbitAngle += glm::radians<float>(fmod(time * orbitSpeed, Constants::degreeCircle));
	model = glm::translate(
		model,
		glm::vec3(distance * glm::cos(currentOrbitAngle), 0.0f, -distance * glm::sin(currentOrbitAngle))
	);

	/* Tilt the axis */
	model = glm::rotate(model, glm::radians<float>(axisTilt), Constants::zAxis());

	/* Draw all satelites */
	for (SolarBody *sat : satellites) {
		sat->render(model, view, projection, time);
	}

	/* Draw axis */
	if (axis) {
		objectAxis->render(view, projection, model);
	}

	/* Rotate Object */
	currentRotationAngle += glm::radians<float>(fmod(time * rotationSpeed, Constants::degreeCircle));
	model = glm::rotate(model, currentRotationAngle, Constants::yAxis());

	/* Draw the actual object */
	objectModel->render(view, projection, model);
}

void SolarBody::addSatellite(SolarBody *satellite)
{
	satellites.push_back(satellite);
}

void SolarBody::increaseAxisTilt(double value)
{
	if (axisTilt < Constants::maxTilt) {
		axisTilt += value;
	}
}

void SolarBody::decreaseAxisTilt(double value)
{
	if (axisTilt > Constants::minTilt) {
		axisTilt -= value;
	}
}

void SolarBody::increaseYOffset(double value)
{
	yOffset += value;
}

void SolarBody::decreaseYOffset(double value)
{
	yOffset -= value;
}

void SolarBody::drawAxis(bool value)
{
	axis = value;
}

void SolarBody::drawOrbit(bool value)
{
	orbit = value;
}
