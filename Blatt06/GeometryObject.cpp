#include "GeometryObject.h"

GeometryObject::GeometryObject(VertexArrayObject* geometry, VertexArrayObject* vNormals, VertexArrayObject* fNormals, VertexArrayObject* bounds)
	: geometry(geometry), vNormals(vNormals), fNormals(fNormals), bounds(bounds),
	showGeo(true), showVN(false), showFN(false), showBox(false)
{
}

GeometryObject::GeometryObject(VertexArrayObject * geometry)
	: GeometryObject(geometry, nullptr, nullptr, nullptr)
{
}

GeometryObject::~GeometryObject()
{
}

void GeometryObject::render(Transforms tf)
{
	if (geometry && showGeo) {
		geometry->render(tf);
	}

	if (vNormals && showVN) {
		vNormals->render(tf);
	}

	if (fNormals && showFN) {
		fNormals->render(tf);
	}

	if (bounds && showBox) {
		bounds->render(tf);
	}
}

void GeometryObject::showGeometry(bool value)
{
	showGeo = value;
}

void GeometryObject::showVertexNormals(bool value)
{
	showVN = value;
}

void GeometryObject::showFaceNormals(bool value)
{
	showFN = value;
}

void GeometryObject::showBoundingBox(bool value)
{
	showBox = value;
}

void GeometryObject::setGeometryShader(cg::GLSLProgram & shader)
{
	geometry->setShader(shader);
}

void GeometryObject::SetNormalShader(cg::GLSLProgram & shader)
{
	vNormals->setShader(shader);
	fNormals->setShader(shader);
	bounds->setShader(shader);
}

void GeometryObject::setGeometry(VertexArrayObject * geometry)
{
	this->geometry = geometry;
}

void GeometryObject::setVertexNormals(VertexArrayObject * normals)
{
	this->vNormals = normals;
}

void GeometryObject::setFaceNormals(VertexArrayObject * normals)
{
	this->fNormals = normals;
}

void GeometryObject::setBoundingBox(VertexArrayObject * box)
{
	bounds = box;
}

void GeometryObject::useLighting(bool value)
{
	geometry->useLighting(value);
}
