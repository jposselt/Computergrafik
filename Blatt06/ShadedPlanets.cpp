#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GLTools.h"
#include "ShadedPlanets.h"
#include "Circle.h"
#include "Line.h"
#include "Sphere.h"
#include "Constants.h"
#include "ObjParser.h"
#include "MeshAnalyser.h"


/// <summary>
/// Initializes a new instance of the <see cref="ShadedPlanets"/> class.
/// </summary>
ShadedPlanets::ShadedPlanets()
	: timeScaleFactor(Constants::initialTimeScaleFactor), shipTimeScaleFactor(Constants::ship::timeScaleFactor)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="ShadedPlanets"/> class.
/// </summary>
ShadedPlanets::~ShadedPlanets()
{
	delete planetSystem;
}

/// <summary>
/// Initializes this instance.
/// </summary>
void ShadedPlanets::init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(Constants::clearColor().x, Constants::clearColor().y, Constants::clearColor().z, Constants::clearColor().w);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Compile shaders
	initShader(simple, Constants::simpleVertexShader, Constants::simpleFragmentShader);
	initShader(flat, Constants::flatVertexShader, Constants::flatFragmentShader);
	initShader(gouraud, Constants::gouraudVertexShader, Constants::gouraudFragmentShader);
	initShader(phong, Constants::phongVertexShader, Constants::phongFragmentShader);

	// List of available shaders
	shaders.push_back(&flat);
	//shaders.push_back(&gouraud);
	//shaders.push_back(&phong);

	// Temporary variables
	GeometryObject *model, *axis, *orbit;

	// Parser for obj files
	ObjParser parser;

	// Spaceship
	Mesh shipMesh;
	parser.loadMesh(Constants::ship::objFile, shipMesh);
	//MeshAnalyser::analyse(shipMesh);
	model = new GeometryObject(shipMesh, *(shaders.at(0)), simple);
	model->scale(Constants::ship::scaleFactor);
	model->useTexture(Constants::ship::texture);
	axis = nullptr;
	orbit = new Circle(simple, Constants::ship::distance);
	ship = new SolarBody(
		model,
		axis,
		orbit,
		Constants::ship::distance,
		Constants::ship::orbitSpeed,
		Constants::ship::rotationSpeed,
		Constants::ship::tilt,
		Constants::ship::offset,
		Constants::ship::startAngle,
		Constants::ship::startRotation
	);

	// Sun
	Mesh objectMesh;
	parser.loadMesh(Constants::objFile, objectMesh);
	objectMesh.calculateNormals();
	//MeshAnalyser::analyse(objectMesh);
	model = new GeometryObject(objectMesh, *(shaders.at(0)), simple);
	model->useTexture(Constants::Sun::texture);
	model->calcTexCoords(Constants::Sun::projCylinderOrigin(), Constants::Sun::projCylinderCenterAxis());
	axis = nullptr;
	orbit = nullptr;
	planetSystem = new SolarBody(
		model,
		axis,
		orbit,
		Constants::Sun::distance,
		Constants::Sun::orbitSpeed,
		Constants::Sun::rotationSpeed,
		Constants::Sun::tilt,
		Constants::Sun::offset,
		Constants::Sun::startAngle,
		Constants::Sun::startRotation
	);

	// Planet 1
	model = new Sphere(*(shaders.at(0)), Constants::Planet_1::radius, Constants::stacks, Constants::slices, true);
	axis = new Line(simple, -Constants::axisScale * (float)Constants::Planet_1::radius * Constants::yAxis(), Constants::axisScale * (float)Constants::Planet_1::radius * Constants::yAxis());
	orbit = new Circle(simple, Constants::Planet_1::distance);
	planet_1 = new SolarBody(
		model,
		axis,
		orbit,
		Constants::Planet_1::distance,
		Constants::Planet_1::orbitSpeed,
		Constants::Planet_1::rotationSpeed,
		Constants::Planet_1::tilt,
		Constants::Planet_1::offset,
		Constants::Planet_1::startAngle,
		Constants::Planet_1::startRotation
	);
	model->setGeometryColor(Constants::Planet_1::color());
	axis->setGeometryColor(Constants::Planet_1::color());
	orbit->setGeometryColor(Constants::Planet_1::color());

	// Planet 1 Moons
	for (int i = 0; i < Constants::Planet_1::Moons::nCenter; i++) {
		model = new Sphere(*(shaders.at(0)), Constants::Planet_1::Moons::radius, Constants::stacks, Constants::slices, true);
		axis = new Line(simple, -Constants::axisScale * (float)Constants::Planet_1::Moons::radius * Constants::yAxis(), Constants::axisScale * (float)Constants::Planet_1::Moons::radius * Constants::yAxis());
		orbit = new Circle(simple, Constants::Planet_1::Moons::distance);
		SolarBody *moon = new SolarBody(
			model,
			axis,
			orbit,
			Constants::Planet_1::Moons::distance,
			Constants::Planet_1::Moons::orbitSpeed,
			Constants::Planet_1::Moons::rotationSpeed,
			Constants::Planet_1::Moons::tilt,
			Constants::Planet_1::Moons::offset,
			Constants::degreeCircle / Constants::Planet_1::Moons::nCenter * i,
			Constants::Planet_1::Moons::startRotation
		);
		moon->drawAxis(false);
		model->setGeometryColor(Constants::Planet_1::Moons::color());
		axis->setGeometryColor(Constants::Planet_1::Moons::color());
		orbit->setGeometryColor(Constants::Planet_1::Moons::color());
		planet_1->addSatellite(moon);
	}

	// Planet 2
	model = new Sphere(*(shaders.at(0)), Constants::Planet_2::radius, Constants::stacks, Constants::slices, true);
	axis = new Line(simple, -Constants::axisScale * (float)Constants::Planet_2::radius * Constants::yAxis(), Constants::axisScale * (float)Constants::Planet_2::radius * Constants::yAxis());
	orbit = new Circle(simple, Constants::Planet_2::distance);
	planet_2 = new SolarBody(
		model,
		axis,
		orbit,
		Constants::Planet_2::distance,
		Constants::Planet_2::orbitSpeed,
		Constants::Planet_2::rotationSpeed,
		Constants::Planet_2::tilt,
		Constants::Planet_2::offset,
		Constants::Planet_2::startAngle,
		Constants::Planet_2::startRotation
	);
	model->setGeometryColor(Constants::Planet_2::color());
	axis->setGeometryColor(Constants::Planet_2::color());
	orbit->setGeometryColor(Constants::Planet_2::color());
	
	// Planet 2 Moons
	for (int i = 0; i < Constants::Planet_2::Moons::nUpper; i++) {
		model = new Sphere(*(shaders.at(0)), Constants::Planet_2::Moons::radius, Constants::stacks, Constants::slices, true);
		axis = new Line(simple, -Constants::axisScale * (float)Constants::Planet_2::Moons::radius * Constants::yAxis(), Constants::axisScale * (float)Constants::Planet_2::Moons::radius * Constants::yAxis());
		orbit = new Circle(simple, Constants::Planet_2::Moons::distance);
		SolarBody *moon = new SolarBody(
			model,
			axis,
			orbit,
			Constants::Planet_2::Moons::distance,
			Constants::Planet_2::Moons::orbitSpeed,
			Constants::Planet_2::Moons::rotationSpeed,
			Constants::Planet_2::Moons::tilt,
			Constants::Planet_2::Moons::upperOffset,
			Constants::degreeCircle / Constants::Planet_2::Moons::nUpper * i,
			Constants::Planet_2::Moons::startRotation
		);
		moon->drawAxis(false);
		model->setGeometryColor(Constants::Planet_2::Moons::color());
		axis->setGeometryColor(Constants::Planet_2::Moons::color());
		orbit->setGeometryColor(Constants::Planet_2::Moons::color());
		planet_2->addSatellite(moon);
	}

	for (int i = 0; i < Constants::Planet_2::Moons::nCenter; i++) {
		model = new Sphere(*(shaders.at(0)), Constants::Planet_2::Moons::radius, Constants::stacks, Constants::slices, true);
		axis = new Line(simple, -Constants::axisScale * (float)Constants::Planet_2::Moons::radius * Constants::yAxis(), Constants::axisScale * (float)Constants::Planet_2::Moons::radius * Constants::yAxis());
		orbit = new Circle(simple, Constants::Planet_2::Moons::distance);
		SolarBody *moon = new SolarBody(
			model,
			axis,
			orbit,
			Constants::Planet_2::Moons::distance,
			Constants::Planet_2::Moons::orbitSpeed,
			Constants::Planet_2::Moons::rotationSpeed,
			Constants::Planet_2::Moons::tilt,
			Constants::Planet_2::Moons::centerOffset,
			Constants::degreeCircle / Constants::Planet_2::Moons::nCenter * i,
			Constants::Planet_2::Moons::startRotation
		);
		moon->drawAxis(false);
		model->setGeometryColor(Constants::Planet_2::Moons::color());
		axis->setGeometryColor(Constants::Planet_2::Moons::color());
		orbit->setGeometryColor(Constants::Planet_2::Moons::color());
		planet_2->addSatellite(moon);
	}

	for (int i = 0; i < Constants::Planet_2::Moons::nLower; i++) {
		model = new Sphere(*(shaders.at(0)), Constants::Planet_2::Moons::radius, Constants::stacks, Constants::slices, true);
		axis = new Line(simple, -Constants::axisScale * (float)Constants::Planet_2::Moons::radius * Constants::yAxis(), Constants::axisScale * (float)Constants::Planet_2::Moons::radius * Constants::yAxis());
		orbit = new Circle(simple, Constants::Planet_2::Moons::distance);
		SolarBody *moon = new SolarBody(
			model,
			axis,
			orbit,
			Constants::Planet_2::Moons::distance,
			Constants::Planet_2::Moons::orbitSpeed,
			Constants::Planet_2::Moons::rotationSpeed,
			Constants::Planet_2::Moons::tilt,
			Constants::Planet_2::Moons::lowerOffset,
			Constants::degreeCircle / Constants::Planet_2::Moons::nLower * i,
			Constants::Planet_2::Moons::startRotation
		);
		moon->drawAxis(false);
		model->setGeometryColor(Constants::Planet_2::Moons::color());
		axis->setGeometryColor(Constants::Planet_2::Moons::color());
		orbit->setGeometryColor(Constants::Planet_2::Moons::color());
		planet_2->addSatellite(moon);
	}

	// Add planets to system
	//planetSystem->addSatellite(planet_1);
	//planetSystem->addSatellite(planet_2);

}

/// <summary>
/// Renders the solar system.
/// </summary>
/// <param name="model">The model matrix.</param>
/// <param name="view">The view matrix.</param>
/// <param name="projection">The projection matrix.</param>
void ShadedPlanets::render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int elapsedTime = getElapsedTime();
	planetSystem->render(model, view, projection, timeScaleFactor * elapsedTime);
	//ship->render(model, view, projection, timeScaleFactor * shipTimeScaleFactor * elapsedTime);
}

/// <summary>
/// Gets the elapsed time in milliseconds.
/// </summary>
/// <returns></returns>
int ShadedPlanets::getElapsedTime()
{
	static int previousTime = 0;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

/// <summary>
/// Pass lighting information to the shader program.
/// </summary>
/// <param name="position">The position/direction of the light source.</param>
/// <param name="direct">RGB color vector of the direct light.</param>
/// <param name="ambient">RGB color vector of the ambient light.</param>
void ShadedPlanets::setLight(glm::vec4 position, glm::vec3 direct, glm::vec3 ambient)
{
	for (std::vector<cg::GLSLProgram*>::iterator it = shaders.begin(); it != shaders.end(); ++it) {
		(*it)->use();
		(*it)->setUniform("lightPosition", position);
		(*it)->setUniform("directLight", direct);
		(*it)->setUniform("ambientLight", ambient);
	}
}

/// <summary>
/// Pass the camera position information to the shader program.
/// </summary>
/// <param name="camera">The camera.</param>
void ShadedPlanets::setCamera(glm::vec3 camera) {
	for (std::vector<cg::GLSLProgram*>::iterator it = shaders.begin(); it != shaders.end(); ++it) {
		(*it)->use();
		(*it)->setUniform("cameraPosition", camera);
	}
}

/// <summary>
/// Increases the animation speed.
/// </summary>
void ShadedPlanets::increaseSpeed()
{
	timeScaleFactor += Constants::timeScaleStepSize;
}

/// <summary>
/// Decreases the animation speed.
/// </summary>
void ShadedPlanets::decreaseSpeed()
{
	timeScaleFactor -= Constants::timeScaleStepSize;
}

/// <summary>
/// Increases the ship speed.
/// </summary>
void ShadedPlanets::increaseShipSpeed()
{
	shipTimeScaleFactor += Constants::ship::timeScaleStepSize;
}

/// <summary>
/// Decreases the ship speed.
/// </summary>
void ShadedPlanets::decreaseShipSpeed()
{
	shipTimeScaleFactor -= Constants::ship::timeScaleStepSize;
}

/// <summary>
/// Rotate main object around its x-axis
/// </summary>
/// <param name="value">The value.</param>
void ShadedPlanets::rotateX(float value)
{
	planetSystem->rotateX(value);
}

/// <summary>
/// Rotate main object around its z-axis
/// </summary>
/// <param name="value">The value.</param>
void ShadedPlanets::rotateY(float value)
{
	planetSystem->rotateY(value);
}

/// <summary>
/// Rotate main object around its z-axis
/// </summary>
/// <param name="value">The value.</param>
void ShadedPlanets::rotateZ(float value)
{
	planetSystem->rotateZ(value);
}

/// <summary>
/// Shows the vertex normals.
/// </summary>
/// <param name="value">if set to <c>true</c> [value].</param>
void ShadedPlanets::showVertexNormals(bool value)
{
	planetSystem->showVertexNormals(value);
}

/// <summary>
/// Shows the face normals.
/// </summary>
/// <param name="value">if set to <c>true</c> [value].</param>
void ShadedPlanets::showFaceNormals(bool value)
{
	planetSystem->showFaceNormals(value);
}

/// <summary>
/// Shows the bounding box.
/// </summary>
/// <param name="value">if set to <c>true</c> [value].</param>
void ShadedPlanets::showBoundingBox(bool value)
{
	planetSystem->showBoundingBox(value);
}

/// <summary>
/// Shows the ship normals.
/// </summary>
/// <param name="value">if set to <c>true</c> [value].</param>
void ShadedPlanets::showShipNormals(bool value)
{
	ship->showVertexNormals(value);
}

/// <summary>
/// Scales the main object.
/// </summary>
/// <param name="value">The value.</param>
void ShadedPlanets::scale(float value)
{
	planetSystem->scale(value);
}

/// <summary>
/// Switches the shader.
/// </summary>
void ShadedPlanets::switchShader()
{
	static int index = 0;
	index = (index + 1) % shaders.size();
	planetSystem->setShader( *(shaders.at(index)) );
	ship->setShader(*(shaders.at(index)));
}

/// <summary>
/// Increases the system y offset.
/// </summary>
void ShadedPlanets::increaseSystemYOffset()
{
	planetSystem->increaseYOffset(Constants::yStepSize);
}

/// <summary>
/// Decreases the system y offset.
/// </summary>
void ShadedPlanets::decreaseSystemYOffset()
{
	planetSystem->decreaseYOffset(Constants::yStepSize);
}

/// <summary>
/// Increases the y offset of the first planet.
/// </summary>
void ShadedPlanets::increasePlanet1YOffset()
{
	planet_1->increaseYOffset(Constants::yStepSize);
}

/// <summary>
/// Decreases the y offset of the first planet.
/// </summary>
void ShadedPlanets::decreasePlanet1YOffset()
{
	planet_1->decreaseYOffset(Constants::yStepSize);
}

/// <summary>
/// Increases the axis tilt of the second planet.
/// </summary>
void ShadedPlanets::increasePlanet2Tilt()
{
	planet_2->increaseAxisTilt(Constants::tiltStepSize);
}

/// <summary>
/// Decreases the axis tilt of the second planet.
/// </summary>
void ShadedPlanets::decreasePlanet2Tilt()
{
	planet_2->decreaseAxisTilt(Constants::tiltStepSize);
}

/// <summary>
/// Initializes the shader.
/// </summary>
/// <param name="program">The shader program to initialize.</param>
/// <param name="vert">Vertex shader file.</param>
/// <param name="frag">Fragment shader file.</param>
void ShadedPlanets::initShader(cg::GLSLProgram & program, const std::string & vert, const std::string & frag)
{
	if (!program.compileShaderFromFile(vert.c_str(), cg::GLSLShader::VERTEX))
	{
		throw std::runtime_error("COMPILE VERTEX: " + program.log());
	}

	if (!program.compileShaderFromFile(frag.c_str(), cg::GLSLShader::FRAGMENT))
	{
		throw std::runtime_error("COMPILE FRAGMENT: " + program.log());
	}

	if (!program.link())
	{
		throw std::runtime_error("LINK: " + program.log());
	}
}
