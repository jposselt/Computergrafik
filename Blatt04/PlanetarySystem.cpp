#include "PlanetarySystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <GL/freeglut.h>

PlanetarySystem::PlanetarySystem(cg::GLSLProgram *prog)
	: program(prog),
	model(glm::mat4x4(1.0f)),
	systemYOffset(0.0),
	planet1YOffset(0.0),
	planet2Tilt(45.0),
	speedFactor(1.0),
	lastRenderTime(0),
	elapsedTime(0)
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
	/* Calculate elapsed time */
	int currentTime = glutGet( GLUT_ELAPSED_TIME );
	elapsedTime = currentTime - lastRenderTime;
	lastRenderTime = currentTime;

	/* Build the scene */
	matrixStack.push(model);
	model = glm::translate(model, glm::vec3(0.0f, systemYOffset, 0.0f)); // Global Y Offset

		/* Sun */
		sun->draw(projection * view * model);
		axis->draw(projection * view * model);

		/* Planet 1 */
		drawPlanet1(elapsedTime);

		/* Planet 2 */
		drawPlanet2(elapsedTime);

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

void PlanetarySystem::increaseSpeed()
{
	speedFactor += speedFactorStep;
}

void PlanetarySystem::decreaseSpeed()
{
	speedFactor -= speedFactorStep;
}

void PlanetarySystem::drawPlanet1(int elapsedTime)
{
	static float currentOrbitAngle = glm::radians<float>(planet1StartAngle);
	static float currentRotationAngle = 0.0f; // radians

	matrixStack.push(model);

	/* Adjustable Y offset*/
	model = glm::translate(model, glm::vec3(0.0f, planet1YOffset, 0.0f));

	/* Orbit position */
	currentOrbitAngle += glm::radians<float>(elapsedTime * speedFactor * planet1OrbitSpeed);
	model = glm::translate(
		model,
		glm::vec3(planet1Distance * glm::cos(currentOrbitAngle), 0.0f , -planet1Distance * glm::sin(currentOrbitAngle))
	);

	/* Planet with rotation */
	matrixStack.push(model);
	currentRotationAngle += glm::radians<float>(elapsedTime * speedFactor * planet1RotationSpeed);
	model = glm::rotate(model, currentRotationAngle, yAxis);
	planet->draw(projection * view * model);
	model = matrixStack.top();
	matrixStack.pop();

	/* Axis */
	axis->draw(projection * view * model);

	/* Moons */
	drawPlanet1Moons(elapsedTime);

	model = matrixStack.top();
	matrixStack.pop();
}

void PlanetarySystem::drawPlanet1Moons(int elapsedTime)
{
	static float currentOrbitAngle = 0.0f; // radians
	currentOrbitAngle += glm::radians<float>(elapsedTime * speedFactor * planet1MoonRotationSpeed);

	for (int i = 0; i < nMoonsPlanet1; i++)
	{
		matrixStack.push(model);
		model = glm::rotate(
			model,
			currentOrbitAngle + glm::two_pi<float>() / nMoonsPlanet1 * i,
			yAxis);
		model = glm::translate(model, glm::vec3(planet1MoonDistance, 0.0f, 0.0f));
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}
}

void PlanetarySystem::drawPlanet2(int elapsedTime)
{
	static float currentOrbitAngle = glm::radians<float>(planet2StartAngle);
	static float currentRotationAngle = 0.0f; // radians

	matrixStack.push(model);

	/* Orbit position */
	currentOrbitAngle += glm::radians<float>(elapsedTime * speedFactor * planet2OrbitSpeed);
	model = glm::translate(
		model,
		glm::vec3(planet2Distance * glm::cos(currentOrbitAngle), 0.0f, -planet2Distance * glm::sin(currentOrbitAngle))
	);

	/* Adjustable tilt */
	model = glm::rotate(model, glm::radians<float>(planet2Tilt), zAxis);

	/* Planet with rotation */
	matrixStack.push(model);
	currentRotationAngle += glm::radians<float>(elapsedTime * speedFactor * planet2RotationSpeed);
	model = glm::rotate(model, currentRotationAngle, yAxis);
	planet->draw(projection * view * model);
	model = matrixStack.top();
	matrixStack.pop();

	/* Axis */
	axis->draw(projection * view * model);

	/* Moons */
	drawPlanet2Moons(elapsedTime);

	model = matrixStack.top();
	matrixStack.pop();
}

void PlanetarySystem::drawPlanet2Moons(int elapsedTime)
{
	static float currentOrbitAngle = 0.0f; // radians
	currentOrbitAngle += glm::radians<float>(elapsedTime * speedFactor * planet2MoonRotationSpeed);

	for (int i = 0; i < nMoonsUpPlanet2; i++)
	{
		matrixStack.push(model);
		model = glm::translate(model, glm::vec3(0.0f, planet2UpperMoonsOffset, 0.0f)); // Y Offset
		model = glm::rotate(
			model,
			currentOrbitAngle + glm::two_pi<float>() / nMoonsUpPlanet2 * i,
			yAxis);
		model = glm::translate(model, glm::vec3(planet2MoonDistance, 0.0f, 0.0f));
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
			currentOrbitAngle + glm::two_pi<float>() / nMoonsDownPlanet2 * i,
			glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(planet2MoonDistance, 0.0f, 0.0f));
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
			currentOrbitAngle + glm::two_pi<float>() / nMoonsCenterPlanet2 * i,
			yAxis);
		model = glm::translate(model, glm::vec3(planet2MoonDistance, 0.0f, 0.0f));
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}
}
