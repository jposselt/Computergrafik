#pragma once
#include "glm/glm.hpp"

struct MaterialInfo
{
	glm::vec3 Ka;		//Ambient reflectivity
	glm::vec3 Kd;		//Diffuse reflectivity
	glm::vec3 Ks;		//Specular reflectivity
	float Shininess;	//Specular shininess factor
};

//namespace Material {
//	MaterialInfo DefaultMaterial;
//}