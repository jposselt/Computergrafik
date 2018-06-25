#pragma once
#include "GeometryObject.h"
class Sphere :
	public GeometryObject
{
public:
	Sphere(cg::GLSLProgram & shader, double radius, unsigned int stacks, unsigned int slices, bool lighting);
	Sphere(cg::GLSLProgram & shader, double radius, bool lighting);
	Sphere(cg::GLSLProgram & shader, bool lighting);
	~Sphere();

private:
	VertexArrayObject* geometry;
};

