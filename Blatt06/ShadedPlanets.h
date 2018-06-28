#pragma once

#include "GLSLProgram.h"
#include "SolarBody.h"

/// <summary>
/// A solar system with a sun, two planets and 13 moon
/// </summary>
class ShadedPlanets
{
public:
	ShadedPlanets();
	~ShadedPlanets();

	void init();
	void render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection);
	void setLight(glm::vec4 position, glm::vec3 direct, glm::vec3 ambient);
	void setCamera(glm::vec3 camera);

	void increaseSystemYOffset();
	void decreaseSystemYOffset();
	void increasePlanet1YOffset();
	void decreasePlanet1YOffset();
	void increasePlanet2Tilt();
	void decreasePlanet2Tilt();
	void increaseSpeed();
	void decreaseSpeed();
	void increaseShipSpeed();
	void decreaseShipSpeed();
	void rotateX(float value);
	void rotateY(float value);
	void rotateZ(float value);
	void showVertexNormals(bool value);
	void showFaceNormals(bool value);
	void showBoundingBox(bool value);
	void scale(float value);
	void switchShader();

private:
	cg::GLSLProgram simple;
	cg::GLSLProgram flat, gouraud, phong;
	std::vector<cg::GLSLProgram*> shaders;
	SolarBody *planetSystem, *planet_1, *planet_2, *ship;
	double timeScaleFactor;
	double shipTimeScaleFactor;

	int getElapsedTime();
	
	static void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);
	
};

