#include <glm/gtc/matrix_transform.hpp>
#include <cmath>       /* fmod */

#include "SolarBody.h"
#include "Constants.h"

/// <summary>
/// Initializes a new instance of the <see cref="SolarBody"/> class.
/// </summary>
/// <param name="simple">Shader for rendering simple objects with no surface lighting</param>
/// <param name="lighting">Shader for rendering with surface lighting.</param>
/// <param name="distance">The orbit radius.</param>
/// <param name="radius">The object radius.</param>
/// <param name="orbitSpeed">The orbit speed.</param>
/// <param name="rotationSpeed">The rotation speed.</param>
/// <param name="color">The object color.</param>
/// <param name="axisTilt">The tilt of the rotation axis.</param>
/// <param name="yOffset">The y offset.</param>
/// <param name="startAngle">The start angle on the orbit.</param>
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

/// <summary>
/// Finalizes an instance of the <see cref="SolarBody"/> class.
/// </summary>
SolarBody::~SolarBody()
{
	delete objectModel;
	delete objectAxis;
	delete objectOrbit;

	for (SolarBody *sat : satellites) {
		delete sat;
	}
}

/// <summary>
/// Initializes this instance.
/// </summary>
void SolarBody::init()
{
	objectModel->init(color);
	objectAxis->init(color);
	objectOrbit->init(color);
}

/// <summary>
/// Renders the object and its satellites.
/// </summary>
/// <param name="model">The model matrix.</param>
/// <param name="view">The view matrix.</param>
/// <param name="projection">The projection matrix.</param>
/// <param name="time">Time for animation in milliseconds.</param>
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
