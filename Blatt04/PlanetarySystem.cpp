#include "PlanetarySystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

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
	matrixStack.push(model);
	model = glm::translate(model, glm::vec3(0.0f, systemYOffset, 0.0f)); // Y Offset
	sun->draw(projection * view * model);
	axis->draw(projection * view * model);

		/* 1st planet */
		matrixStack.push(model);
		model = glm::translate(model, glm::vec3(0.0f, planet1YOffset, 0.0f)); // Y Offset
		model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
		planet->draw(projection * view * model);
		axis->draw(projection * view * model);

			/* 1st planet moons */
			for (int i = 0; i < nMoonsPlanet1; i++)
			{
				matrixStack.push(model);
				model = glm::rotate(model, glm::two_pi<float>()/ nMoonsPlanet1 * i, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
				moon->draw(projection * view * model);
				model = matrixStack.top();
				matrixStack.pop();
			}

		model = matrixStack.top();
		matrixStack.pop();

		/* 2nd planets */
		matrixStack.push(model);
		model = glm::translate(model, glm::vec3(-12.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians<float>(planet2Tilt), glm::vec3(0.0f, 0.0f, 1.0f)); // Planet tilt
		planet->draw(projection * view * model);
		axis->draw(projection * view * model);

			/* 2nd planet upper moons */
			for (int i = 0; i < nMoonsUpPlanet2; i++)
			{
				matrixStack.push(model);
				model = glm::translate(model, glm::vec3(0.0f, planet2UpperMoonsOffset, 0.0f)); // Y Offset
				model = glm::rotate(model, glm::two_pi<float>() / nMoonsUpPlanet2 * i, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
				moon->draw(projection * view * model);
				model = matrixStack.top();
				matrixStack.pop();
			}

			/* 2nd planet lower moons */
			for (int i = 0; i < nMoonsDownPlanet2; i++)
			{
				matrixStack.push(model);
				model = glm::translate(model, glm::vec3(0.0f, planet2LowerMoonsOffset, 0.0f)); // Y Offset
				model = glm::rotate(model, glm::two_pi<float>() / nMoonsDownPlanet2 * i, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
				moon->draw(projection * view * model);
				model = matrixStack.top();
				matrixStack.pop();
			}

			/* 2nd planet center moons */
			for (int i = 0; i < nMoonsCenterPlanet2; i++)
			{
				matrixStack.push(model);
				model = glm::rotate(model, glm::two_pi<float>() / nMoonsCenterPlanet2 * i, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
				moon->draw(projection * view * model);
				model = matrixStack.top();
				matrixStack.pop();
			}

		model = matrixStack.top();
		matrixStack.pop();

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
