#include <GL/glew.h>
#include <GL/freeglut.h>
#include "CrazyPlanets.h"
#include "Constants.h"


CrazyPlanets::CrazyPlanets(cg::GLSLProgram *prog)
	: program(prog),
	timeScaleFactor(Constants::initialTimeScaleFactor)
{
}


CrazyPlanets::~CrazyPlanets()
{
	delete planetSystem;
}

void CrazyPlanets::init()
{
	/* Sun */
	planetSystem = new CelestialObject(program,
		Constants::Sun::distance,
		Constants::Sun::radius,
		Constants::Sun::orbitSpeed,
		Constants::Sun::rotationSpeed,
		Constants::Sun::color,
		Constants::Sun::tilt,
		Constants::Sun::offset,
		Constants::Sun::startAngle);

	planetSystem->init();
	planetSystem->drawOrbit(false);

	/* Planet 1 */
	planet_1 = new CelestialObject(program,
		Constants::Planet_1::distance,
		Constants::Planet_1::radius,
		Constants::Planet_1::orbitSpeed,
		Constants::Planet_1::rotationSpeed,
		Constants::Planet_1::color,
		Constants::Planet_1::tilt,
		Constants::Planet_1::offset,
		Constants::Planet_1::startAngle);
		
	planet_1->init();

	/* Planet 1 Moons */
	/*
	for (int i = 0; i < Constants::Planet_1::Moons::nCenter; i++) {

	}
	*/

	/* Planet 2 */
	
	planet_2 = new CelestialObject(program,
		Constants::Planet_2::distance,
		Constants::Planet_2::radius,
		Constants::Planet_2::orbitSpeed,
		Constants::Planet_2::rotationSpeed,
		Constants::Planet_2::color,
		Constants::Planet_2::tilt,
		Constants::Planet_2::offset,
		Constants::Planet_2::startAngle);
		
	planet_2->init();

	/* Planet 2 Moons */
	/*
	for (int i = 0; i < Constants::Planet_2::Moons::nUpper; i++) {

	}

	for (int i = 0; i < Constants::Planet_2::Moons::nCenter; i++) {

	}

	for (int i = 0; i < Constants::Planet_2::Moons::nLower; i++) {

	}
	*/

	/* Add planets to system */
	planetSystem->addSatellite(planet_1);
	planetSystem->addSatellite(planet_2);
}

void CrazyPlanets::draw(glm::mat4x4 mvp)
{
	planetSystem->draw(mvp, timeScaleFactor * getElapsedTime());
}


int CrazyPlanets::getElapsedTime()
{
	static int previousTime = 0;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

void CrazyPlanets::increaseSpeed()
{
	timeScaleFactor += Constants::timeScaleStepSize;
}

void CrazyPlanets::decreaseSpeed()
{
	timeScaleFactor -= Constants::timeScaleStepSize;
}

void CrazyPlanets::increaseSystemYOffset()
{
	planetSystem->increaseYOffset(Constants::yStepSize);
}

void CrazyPlanets::decreaseSystemYOffset()
{
	planetSystem->decreaseYOffset(Constants::yStepSize);
}

void CrazyPlanets::increasePlanet1YOffset()
{
	planet_1->increaseYOffset(Constants::yStepSize);
}

void CrazyPlanets::decreasePlanet1YOffset()
{
	planet_1->decreaseYOffset(Constants::yStepSize);
}

void CrazyPlanets::increasePlanet2Tilt()
{
	planet_2->increaseAxisTilt(Constants::tiltStepSize);
}

void CrazyPlanets::decreasePlanet2Tilt()
{
	planet_2->decreaseAxisTilt(Constants::tiltStepSize);
}