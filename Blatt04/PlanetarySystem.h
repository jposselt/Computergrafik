#pragma once
#include <stack>
#include "GLSLProgram.h"
#include "UnitSphere.h"
#include "PlanetsAxis.h"

class PlanetarySystem
{
public:
	PlanetarySystem(cg::GLSLProgram *prog);
	~PlanetarySystem();
	void init();
	void draw();
	void setView(glm::mat4x4 view);
	void setProjection(glm::mat4x4 projection);
	void increaseSystemYOffset();
	void decreaseSystemYOffset();
	void increasePlanet1YOffset();
	void decreasePlanet1YOffset();
	void increasePlanet2Tilt();
	void decreasePlanet2Tilt();
	void increaseSpeed();
	void decreaseSpeed();

private:
	/* Helper functions for scene drawing */
	void drawPlanet1(int elapsedTime);
	void drawPlanet1Moons(int elapsedTime);
	void drawPlanet2(int elapsedTime);
	void drawPlanet2Moons(int elapsedTime);

	/* Matrix stack */
	std::stack <glm::mat4x4> matrixStack;

	/* Program reference */
	cg::GLSLProgram *program;

	/* Model, View and Projection matrices */
	glm::mat4x4 view;
	glm::mat4x4 projection;
	glm::mat4x4 model;

	/* We use spheres of 3 different sizes to represent the sun, planets and moons */
	UnitSphere *sun;
	UnitSphere *planet;
	UnitSphere *moon;
	PlanetsAxis *axis;

	/* Adjustable values */
	double systemYOffset;
	double planet1YOffset;
	double planet2Tilt; // degree
	double speedFactor;

	/* Time variables*/
	int lastRenderTime;
	int elapsedTime;

	/* General Constants */
	double sunRadius = 1.0;
	double planetRadius = 0.5;
	double moonRadius = 0.2;
	double systemYOffsetStepsize = 0.2;
	double speedFactorStep = 0.2;

	/* Planet 1 Constants */
	int nMoonsPlanet1 = 3;
	double planet1YOffsetStepsize = 0.2;
	double planet1Distance = 6.0;
	double planet1StartAngle = 0.0; // degree
	double planet1OrbitSpeed = 10.0 / 1000.0;        // 10° per second
	double planet1RotationSpeed = 30.0 / 1000.0;     // 30° per second
	double planet1MoonRotationSpeed = 20.0 / 1000.0; // 20° per second

	/* Planet 2 Constants */
	int nMoonsCenterPlanet2 = 2;
	int nMoonsUpPlanet2 = 4;
	int nMoonsDownPlanet2 = 4;
	double planet2UpperMoonsOffset = 1.0;
	double planet2LowerMoonsOffset = -1.0;
	double planet2TiltStepsize = 1.0; // degree
	double planet2MinTilt = 0.0;      // degree
	double planet2MaxTilt = 360.0;    // degree
	double planet2Distance = 12.0;
	double planet2StartAngle = 180.0; // degree
	double planet2OrbitSpeed = 5.0 / 1000.0;         // 5° per second
	double planet2RotationSpeed = 30.0 / 1000.0;     // 30° per second
	double planet2MoonRotationSpeed = 20.0 / 1000.0; // 20° per second
};

