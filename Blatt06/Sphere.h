#pragma once
#include "GeometryObject.h"
class Sphere :
	public GeometryObject
{
public:
	Sphere(cg::GLSLProgram & shader, double radius, unsigned int stacks, unsigned int slices, bool lighting);
	~Sphere();

private:
	double radius;
	unsigned int nStacks;
	unsigned int nSlices;
};

