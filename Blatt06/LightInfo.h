#pragma once
#include "glm/glm.hpp"

struct LightInfo
{
	glm::vec3 Position;	//Light Position in eye-coords
	glm::vec3 La;		//Ambient light intensity
	glm::vec3 Ld;		//Diffuse light intensity
	glm::vec3 Ls;		//Specular light intensity
};

namespace Light {
	LightInfo DefaultLight;
}