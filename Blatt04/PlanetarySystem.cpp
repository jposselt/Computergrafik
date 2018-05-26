#include "PlanetarySystem.h"


PlanetarySystem::PlanetarySystem(cg::GLSLProgram *prog)
	: program(prog), model(glm::mat4x4(1.0f))
{
	sphere = new UnitSphere(program);
}


PlanetarySystem::~PlanetarySystem()
{
	delete sphere;
}


void PlanetarySystem::init()
{
	sphere->init();
}

void PlanetarySystem::draw()
{
	sphere->draw(projection * view * model);
}

void PlanetarySystem::setView(glm::mat4x4 view)
{
	this->view = view;
}

void PlanetarySystem::setProjection(glm::mat4x4 projection)
{
	this->projection = projection;
}
