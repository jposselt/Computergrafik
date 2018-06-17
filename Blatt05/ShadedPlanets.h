#pragma once

#include <iostream>
#include "GLSLProgram.h"
#include "SolarBody.h"

class ShadedPlanets
{
public:
	ShadedPlanets();
	~ShadedPlanets();

	void init();
	void render();
	void resize(int width, int height);

	void increaseSystemYOffset();
	void decreaseSystemYOffset();
	void increasePlanet1YOffset();
	void decreasePlanet1YOffset();
	void increasePlanet2Tilt();
	void decreasePlanet2Tilt();
	void increaseSpeed();
	void decreaseSpeed();
	//void zoomIn();
	//void zoomOut();
	//void toggleLight();

private:
	cg::GLSLProgram programShaded;
	cg::GLSLProgram programSimple;
	SolarBody *planetSystem, *planet_1, *planet_2;
	double timeScaleFactor;
	glm::mat4x4 model, view, projection;
	glm::vec3 eye, center, up;
	float zNear, zFar;

	int getElapsedTime();
	//void setPositionlight();
	//void setDirectionLight();

	static void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);
	
};

