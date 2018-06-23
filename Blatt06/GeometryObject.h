#pragma once
#include "VertexArrayObject.h"

class GeometryObject
{
public:
	GeometryObject(VertexArrayObject* geometry, VertexArrayObject* vNormals, VertexArrayObject* fNormals, VertexArrayObject* bounds);
	GeometryObject(VertexArrayObject* geometry);
	~GeometryObject();

	void render(Transforms tf);

	void showGeometry(bool value);
	void showVertexNormals(bool value);
	void showFaceNormals(bool value);
	void showBoundingBox(bool value);

	void setGeometryShader(cg::GLSLProgram& shader);
	void SetNormalShader(cg::GLSLProgram& shader);
	void setGeometry(VertexArrayObject* geometry);
	void setVertexNormals(VertexArrayObject* normals);
	void setFaceNormals(VertexArrayObject* normals);
	void setBoundingBox(VertexArrayObject* box);
	void useLighting(bool value);

private:
	VertexArrayObject* geometry; // object geometry
	VertexArrayObject* vNormals; // visualization of vertex normals
	VertexArrayObject* fNormals; // visualization of face normals
	VertexArrayObject* bounds;   // bounding box

	bool showGeo;
	bool showVN;
	bool showFN;
	bool showBox;
};

