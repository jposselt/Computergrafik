#pragma once
#include "GLSLProgram.h"
#include "UnitSphere.h"

class PlanetarySystem
{
public:
	PlanetarySystem(cg::GLSLProgram *prog);
	~PlanetarySystem();
	void init();
	void draw();
	void setView(glm::mat4x4 view);
	void setProjection(glm::mat4x4 projection);
private:
	/* Program reference */
	cg::GLSLProgram *program;

	/*  */
	glm::mat4x4 view;
	glm::mat4x4 projection;
	glm::mat4x4 model;

	/*  */
	UnitSphere *sphere;
};

