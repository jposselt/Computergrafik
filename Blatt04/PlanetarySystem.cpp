#include "PlanetarySystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <GL/freeglut.h>

PlanetarySystem::PlanetarySystem(cg::GLSLProgram *prog)
	: program(prog),
	model(glm::mat4x4(1.0f)),
	systemYOffset(0.0),
	planet1YOffset(0.0),
	planet2Tilt(45.0)
{
	sun = new UnitSphere(program);
	planet = new UnitSphere(program);
	moon = new UnitSphere(program);
	axis = new PlanetsAxis(program);
}


PlanetarySystem::~PlanetarySystem()
{
	delete sun;
	delete planet;
	delete moon;
	delete axis;
}


void PlanetarySystem::init()
{
	sun->init();
	planet->init(0.5);
	moon->init(0.2);
	axis->init();
}

void PlanetarySystem::draw()
{
	/*  */
	int currentTime = glutGet( GLUT_ELAPSED_TIME );

	/* Build the scene */
	matrixStack.push(model);
	model = glm::translate(model, glm::vec3(0.0f, systemYOffset, 0.0f)); // Global Y Offset

		/* Sun */
		sun->draw(projection * view * model);
		axis->draw(projection * view * model);

		/* Planet 1 */
		drawPlanet1(currentTime);

		/* Planet 2 */
		drawPlanet2(currentTime);

	model = matrixStack.top();
	matrixStack.pop();
}

void PlanetarySystem::setView(glm::mat4x4 view)
{
	this->view = view;
}

void PlanetarySystem::setProjection(glm::mat4x4 projection)
{
	this->projection = projection;
}

void PlanetarySystem::increaseSystemYOffset()
{
	systemYOffset += systemYOffsetStepsize;
}

void PlanetarySystem::decreaseSystemYOffset()
{
	systemYOffset -= systemYOffsetStepsize;
}

void PlanetarySystem::increasePlanet1YOffset()
{
	planet1YOffset += planet1YOffsetStepsize;
}

void PlanetarySystem::decreasePlanet1YOffset()
{
		planet1YOffset -= planet1YOffsetStepsize;
}

void PlanetarySystem::increasePlanet2Tilt()
{
	if (planet2Tilt < planet2MaxTilt)
	{
		planet2Tilt += planet2TiltStepsize;
	}
}

void PlanetarySystem::decreasePlanet2Tilt()
{
	if (planet2Tilt > planet2MinTilt)
	{
		planet2Tilt -= planet2TiltStepsize;
	}
}

void PlanetarySystem::drawPlanet1(int currentTime)
{
	matrixStack.push(model);

	/* Adjustable Y offset*/
	model = glm::translate(model, glm::vec3(0.0f, planet1YOffset, 0.0f));

	/* Orbit position */
	float angle = glm::radians<float>(currentTime * planet1OrbitSpeed + planet1StartAngle);
	model = glm::translate(
		model,
		glm::vec3(planet1Distance * glm::cos(angle), 0.0f , -planet1Distance * glm::sin(angle))
	);

	/* Planet with rotation */
	matrixStack.push(model);
	model = glm::rotate(model, glm::radians<float>(currentTime * planet1RotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
	planet->draw(projection * view * model);
	model = matrixStack.top();
	matrixStack.pop();

	/* Axis */
	axis->draw(projection * view * model);

	/* Moons */
	drawPlanet1Moons(currentTime);

	model = matrixStack.top();
	matrixStack.pop();
}

void PlanetarySystem::drawPlanet1Moons(int currentTime)
{
	for (int i = 0; i < nMoonsPlanet1; i++)
	{
		matrixStack.push(model);
		model = glm::rotate(
			model,
			glm::radians<float>(currentTime * planet1MoonRotationSpeed) + glm::two_pi<float>() / nMoonsPlanet1 * i,
			glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}
}

void PlanetarySystem::drawPlanet2(int currentTime)
{
	matrixStack.push(model);

	/* Orbit position */
	float angle = glm::radians<float>(currentTime * planet2OrbitSpeed + planet2StartAngle);
	model = glm::translate(
		model,
		glm::vec3(planet2Distance * glm::cos(angle), 0.0f, -planet2Distance * glm::sin(angle))
	);

	/* Adjustable tilt */
	model = glm::rotate(model, glm::radians<float>(planet2Tilt), glm::vec3(0.0f, 0.0f, 1.0f));

	/* Planet with rotation */
	matrixStack.push(model);
	model = glm::rotate(model, glm::radians<float>(currentTime * planet2RotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
	planet->draw(projection * view * model);
	model = matrixStack.top();
	matrixStack.pop();

	/* Axis */
	axis->draw(projection * view * model);

	/* Moons */
	drawPlanet2Moons(currentTime);

	model = matrixStack.top();
	matrixStack.pop();
}

void PlanetarySystem::drawPlanet2Moons(int currentTime)
{
	for (int i = 0; i < nMoonsUpPlanet2; i++)
	{
		matrixStack.push(model);
		model = glm::translate(model, glm::vec3(0.0f, planet2UpperMoonsOffset, 0.0f)); // Y Offset
		model = glm::rotate(
			model,
			glm::radians<float>(currentTime * planet2MoonRotationSpeed) + glm::two_pi<float>() / nMoonsUpPlanet2 * i,
			glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}

	/* Planet 2 lower moons */
	for (int i = 0; i < nMoonsDownPlanet2; i++)
	{
		matrixStack.push(model);
		model = glm::translate(model, glm::vec3(0.0f, planet2LowerMoonsOffset, 0.0f)); // Y Offset
		model = glm::rotate(
			model,
			glm::radians<float>(currentTime * planet2MoonRotationSpeed) + glm::two_pi<float>() / nMoonsDownPlanet2 * i,
			glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}

	/* Planet 2 center moons */
	for (int i = 0; i < nMoonsCenterPlanet2; i++)
	{
		matrixStack.push(model);
		model = glm::rotate(
			model,
			glm::radians<float>(currentTime * planet2MoonRotationSpeed) + glm::two_pi<float>() / nMoonsCenterPlanet2 * i,
			glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}
}
