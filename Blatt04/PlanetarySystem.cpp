#include "PlanetarySystem.h"
#include <glm/gtc/matrix_transform.hpp>

PlanetarySystem::PlanetarySystem(cg::GLSLProgram *prog)
	: program(prog), model(glm::mat4x4(1.0f))
{
	sun = new UnitSphere(program);
	planet = new UnitSphere(program);
	moon = new UnitSphere(program);
}


PlanetarySystem::~PlanetarySystem()
{
	delete sun;
	delete planet;
	delete moon;
}


void PlanetarySystem::init()
{
	sun->init();
	planet->init(0.5);
	moon->init(0.2);
}

void PlanetarySystem::draw()
{
	sun->draw(projection * view * model);

	model = glm::translate(
				glm::mat4(1.0f),
				glm::vec3(6.0f, 0.0f, 0.0f)
	);
	planet->draw(projection * view * model);

	model = glm::translate(
				model,
				glm::vec3(1.0f, 0.0f, 0.0f)
	);
	moon->draw(projection * view * model);

	model = glm::translate(
				glm::mat4(1.0f),
				glm::vec3(-12.0f, 0.0f, 0.0f)
	);
	planet->draw(projection * view * model);

	model = glm::mat4x4(1.0f);
}

void PlanetarySystem::setView(glm::mat4x4 view)
{
	this->view = view;
}

void PlanetarySystem::setProjection(glm::mat4x4 projection)
{
	this->projection = projection;
}
