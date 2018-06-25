#pragma once
#include "VertexArrayObject.h"
#include "Mesh.h"

class GeometryObject
{
public:
	GeometryObject(VertexArrayObject* geometry, VertexArrayObject* vNormals, VertexArrayObject* fNormals, VertexArrayObject* bounds);
	GeometryObject(VertexArrayObject* geometry);
	GeometryObject(Mesh mesh, cg::GLSLProgram& geoShader, cg::GLSLProgram& normalShader);
	~GeometryObject();

	void render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection);

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
	void setGeometryColor(glm::vec3 color);
	void setVertexNormalColor(glm::vec3 color);
	void setFaceNormalColor(glm::vec3 color);
	void setBoundsColor(glm::vec3 color);
	void setMaterial(glm::vec3 material, float shininess);
	void useLighting(bool value);
	void scale(float value);

private:
	VertexArrayObject* geometry; // object geometry
	VertexArrayObject* vNormals; // visualization of vertex normals
	VertexArrayObject* fNormals; // visualization of face normals
	VertexArrayObject* bounds;   // bounding box

	bool showGeo;
	bool showVN;
	bool showFN;
	bool showBox;

	glm::vec3 vertexNormalColor;
	glm::vec3 faceNormalColor;
	glm::vec3 boundsColor;

	unsigned int nVertexNormalIndices;
	unsigned int nFaceNormalIndices;

	float scaleFactor;
};

