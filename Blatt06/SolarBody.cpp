#include <glm/gtc/matrix_transform.hpp>
#include <cmath>       /* fmod */

#include "SolarBody.h"
#include "Constants.h"

SolarBody::SolarBody(GeometryObject* model, GeometryObject* axis, GeometryObject* orbit, double orbitSpeed, double rotationSpeed, double axisTilt, double yOffset, double startAngle)
	: objectModel(model), objectAxis(axis), objectOrbit(orbit),
	distance(distance),
	orbitSpeed(orbitSpeed),
	rotationSpeed(rotationSpeed),
	axisTilt(fmod(axisTilt, Constants::degreeCircle)),
	yOffset(yOffset),
	currentOrbitAngle(glm::radians<float>(startAngle)),
	currentRotationAngle(0.0),
	axis(true),
	orbit(true)
{
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

void SolarBody::render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection, double time)
{
	/* Y-Offset */
	model = glm::translate(model, glm::vec3(0.0f, yOffset, 0.0f));

	/* Draw orbit */
	if (orbit) {
		objectOrbit->render(model, view, projection);
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
		objectAxis->render(model, view, projection);
	}

	/* Rotate Object */
	currentRotationAngle += glm::radians<float>(fmod(time * rotationSpeed, Constants::degreeCircle));
	model = glm::rotate(model, currentRotationAngle, Constants::yAxis());

	/* Draw the actual object */
	objectModel->render(model, view, projection);
}

/// <summary>
/// Add a satellite to the object.
/// </summary>
/// <param name="satellite">The satellite.</param>
void SolarBody::addSatellite(SolarBody *satellite)
{
	satellites.push_back(satellite);
}

/// <summary>
/// Increases the axis tilt (bounded to [0,360] degrees).
/// </summary>
/// <param name="value">The value.</param>
void SolarBody::increaseAxisTilt(double value)
{
	if (axisTilt < Constants::maxTilt) {
		axisTilt += value;
	}
}

/// <summary>
/// Decreases the axis tilt (bounded to [0,360] degrees).
/// </summary>
/// <param name="value">The value.</param>
void SolarBody::decreaseAxisTilt(double value)
{
	if (axisTilt > Constants::minTilt) {
		axisTilt -= value;
	}
}

/// <summary>
/// Increases the y offset.
/// </summary>
/// <param name="value">The value.</param>
void SolarBody::increaseYOffset(double value)
{
	yOffset += value;
}

/// <summary>
/// Decreases the y offset.
/// </summary>
/// <param name="value">The value.</param>
void SolarBody::decreaseYOffset(double value)
{
	yOffset -= value;
}

/// <summary>
/// Draws the objects rotation axis.
/// </summary>
/// <param name="value">if set to <c>true</c> [value].</param>
void SolarBody::drawAxis(bool value)
{
	axis = value;
}

/// <summary>
/// Draws the objects orbit.
/// </summary>
/// <param name="value">if set to <c>true</c> [value].</param>
void SolarBody::drawOrbit(bool value)
{
	orbit = value;
}
