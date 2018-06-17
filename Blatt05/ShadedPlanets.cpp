#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GLTools.h"
#include "ShadedPlanets.h"
#include "Constants.h"


ShadedPlanets::ShadedPlanets()
	: timeScaleFactor(Constants::initialTimeScaleFactor)
{
}

ShadedPlanets::~ShadedPlanets()
{
	delete planetSystem;
}

void ShadedPlanets::init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(Constants::clearColor().x, Constants::clearColor().y, Constants::clearColor().z, Constants::clearColor().w);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Compile shaders
	initShader(programSimple, Constants::simpleVertexShader, Constants::simpleFragmentShader);
	initShader(programShaded, Constants::vertexShader, Constants::fragmentShader);

	/* Sun */
	planetSystem = new SolarBody(
		programSimple,
		programShaded,
		Constants::Sun::distance,
		Constants::Sun::radius,
		Constants::Sun::orbitSpeed,
		Constants::Sun::rotationSpeed,
		Constants::Sun::color(),
		Constants::Sun::tilt,
		Constants::Sun::offset,
		Constants::Sun::startAngle);

	planetSystem->init();
	planetSystem->drawOrbit(false);

	/* Planet 1 */
	planet_1 = new SolarBody(
		programSimple,
		programShaded,
		Constants::Planet_1::distance,
		Constants::Planet_1::radius,
		Constants::Planet_1::orbitSpeed,
		Constants::Planet_1::rotationSpeed,
		Constants::Planet_1::color(),
		Constants::Planet_1::tilt,
		Constants::Planet_1::offset,
		Constants::Planet_1::startAngle);

	planet_1->init();

	/* Planet 1 Moons */
	for (int i = 0; i < Constants::Planet_1::Moons::nCenter; i++) {
		SolarBody *moon = new SolarBody(
			programSimple,
			programShaded,
			Constants::Planet_1::Moons::distance,
			Constants::Planet_1::Moons::radius,
			Constants::Planet_1::Moons::orbitSpeed,
			Constants::Planet_1::Moons::rotationSpeed,
			Constants::Planet_1::Moons::color(),
			Constants::Planet_1::Moons::tilt,
			Constants::Planet_1::Moons::offset,
			Constants::degreeCircle / Constants::Planet_1::Moons::nCenter * i);
		moon->init();
		moon->drawAxis(false);
		planet_1->addSatellite(moon);
	}

	/* Planet 2 */
	planet_2 = new SolarBody(
		programSimple,
		programShaded,
		Constants::Planet_2::distance,
		Constants::Planet_2::radius,
		Constants::Planet_2::orbitSpeed,
		Constants::Planet_2::rotationSpeed,
		Constants::Planet_2::color(),
		Constants::Planet_2::tilt,
		Constants::Planet_2::offset,
		Constants::Planet_2::startAngle);

	planet_2->init();

	/* Planet 2 Moons */
	for (int i = 0; i < Constants::Planet_2::Moons::nUpper; i++) {
		SolarBody *moon = new SolarBody(
			programSimple,
			programShaded,
			Constants::Planet_2::Moons::distance,
			Constants::Planet_2::Moons::radius,
			Constants::Planet_2::Moons::orbitSpeed,
			Constants::Planet_2::Moons::rotationSpeed,
			Constants::Planet_2::Moons::color(),
			Constants::Planet_2::Moons::tilt,
			Constants::Planet_2::Moons::upperOffset,
			Constants::degreeCircle / Constants::Planet_2::Moons::nUpper * i);
		moon->init();
		moon->drawAxis(false);
		planet_2->addSatellite(moon);
	}

	for (int i = 0; i < Constants::Planet_2::Moons::nCenter; i++) {
		SolarBody *moon = new SolarBody(
			programSimple,
			programShaded,
			Constants::Planet_2::Moons::distance,
			Constants::Planet_2::Moons::radius,
			Constants::Planet_2::Moons::orbitSpeed,
			Constants::Planet_2::Moons::rotationSpeed,
			Constants::Planet_2::Moons::color(),
			Constants::Planet_2::Moons::tilt,
			Constants::Planet_2::Moons::centerOffset,
			Constants::degreeCircle / Constants::Planet_2::Moons::nCenter * i);
		moon->init();
		moon->drawAxis(false);
		planet_2->addSatellite(moon);
	}

	for (int i = 0; i < Constants::Planet_2::Moons::nLower; i++) {
		SolarBody *moon = new SolarBody(
			programSimple,
			programShaded,
			Constants::Planet_2::Moons::distance,
			Constants::Planet_2::Moons::radius,
			Constants::Planet_2::Moons::orbitSpeed,
			Constants::Planet_2::Moons::rotationSpeed,
			Constants::Planet_2::Moons::color(),
			Constants::Planet_2::Moons::tilt,
			Constants::Planet_2::Moons::lowerOffset,
			Constants::degreeCircle / Constants::Planet_2::Moons::nLower * i);
		moon->init();
		moon->drawAxis(false);
		planet_2->addSatellite(moon);
	}

	/* Add planets to system */
	planetSystem->addSatellite(planet_1);
	planetSystem->addSatellite(planet_2);
}

void ShadedPlanets::render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	planetSystem->render(model, view, projection, timeScaleFactor * getElapsedTime());
}

int ShadedPlanets::getElapsedTime()
{
	static int previousTime = 0;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

void ShadedPlanets::setLight(glm::vec4 position, glm::vec3 direct, glm::vec3 ambient)
{
	programShaded.use();
	programShaded.setUniform("lightPosition", position);
	programShaded.setUniform("directLight", direct);
	programShaded.setUniform("ambientLight", ambient);
}

void ShadedPlanets::setCamera(glm::vec3 camera) {
	programShaded.use();
	programShaded.setUniform("cameraPosition", camera);
}

void ShadedPlanets::increaseSpeed()
{
	timeScaleFactor += Constants::timeScaleStepSize;
}

void ShadedPlanets::decreaseSpeed()
{
	timeScaleFactor -= Constants::timeScaleStepSize;
}

void ShadedPlanets::increaseSystemYOffset()
{
	planetSystem->increaseYOffset(Constants::yStepSize);
}

void ShadedPlanets::decreaseSystemYOffset()
{
	planetSystem->decreaseYOffset(Constants::yStepSize);
}

void ShadedPlanets::increasePlanet1YOffset()
{
	planet_1->increaseYOffset(Constants::yStepSize);
}

void ShadedPlanets::decreasePlanet1YOffset()
{
	planet_1->decreaseYOffset(Constants::yStepSize);
}

void ShadedPlanets::increasePlanet2Tilt()
{
	planet_2->increaseAxisTilt(Constants::tiltStepSize);
}

void ShadedPlanets::decreasePlanet2Tilt()
{
	planet_2->decreaseAxisTilt(Constants::tiltStepSize);
}

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
