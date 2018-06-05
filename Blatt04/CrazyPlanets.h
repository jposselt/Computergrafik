#pragma once
#include "CelestialObject.h"

class CrazyPlanets
{
public:
	CrazyPlanets(cg::GLSLProgram *prog);
	~CrazyPlanets();

	void init();
	void draw(glm::mat4x4 mvp);

	void increaseSystemYOffset();
	void decreaseSystemYOffset();
	void increasePlanet1YOffset();
	void decreasePlanet1YOffset();
	void increasePlanet2Tilt();
	void decreasePlanet2Tilt();
	void increaseSpeed();
	void decreaseSpeed();

private:
	/* Program reference */
	cg::GLSLProgram *program;

	/* Animation speed */
	double timeScaleFactor;

	/* Solar System */
	CelestialObject *planetSystem, *planet_1, *planet_2;

	/* Time function */
	int getElapsedTime();


};

