#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GLTools.h"
#include "ShadedPlanets.h"
#include "Constants.h"


/// <summary>
/// Initializes a new instance of the <see cref="ShadedPlanets"/> class.
/// </summary>
ShadedPlanets::ShadedPlanets()
	: timeScaleFactor(Constants::initialTimeScaleFactor)
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

/// <summary>
/// Renders the solar system.
/// </summary>
/// <param name="model">The model matrix.</param>
/// <param name="view">The view matrix.</param>
/// <param name="projection">The projection matrix.</param>
void ShadedPlanets::render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	planetSystem->render(model, view, projection, timeScaleFactor * getElapsedTime());
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
	programShaded.use();
	programShaded.setUniform("lightPosition", position);
	programShaded.setUniform("directLight", direct);
	programShaded.setUniform("ambientLight", ambient);
}

/// <summary>
/// Pass the camera position information to the shader program.
/// </summary>
/// <param name="camera">The camera.</param>
void ShadedPlanets::setCamera(glm::vec3 camera) {
	programShaded.use();
	programShaded.setUniform("cameraPosition", camera);
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
