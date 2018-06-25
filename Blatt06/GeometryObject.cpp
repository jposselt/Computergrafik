#include <glm/gtc/matrix_transform.hpp>
#include "GeometryObject.h"
#include "Constants.h"

GeometryObject::GeometryObject(VertexArrayObject* geometry, VertexArrayObject* vNormals, VertexArrayObject* fNormals, VertexArrayObject* bounds)
	: geometry(geometry), vNormals(vNormals), fNormals(fNormals), bounds(bounds),
	showGeo(true), showVN(false), showFN(false), showBox(false),
	vertexNormalColor(Constants::defaultVNColor()), faceNormalColor(Constants::defaultFNColor()), boundsColor(Constants::defaultColor()), scaleFactor(1.0f)
{
}

GeometryObject::GeometryObject(VertexArrayObject * geometry)
	: GeometryObject(geometry, nullptr, nullptr, nullptr)
{
}

GeometryObject::GeometryObject(Mesh mesh, cg::GLSLProgram& geoShader, cg::GLSLProgram& normalShader)
	: showGeo(true), showVN(false), showFN(false), showBox(false),
	vertexNormalColor(Constants::defaultVNColor()), faceNormalColor(Constants::defaultFNColor()), boundsColor(Constants::defaultColor()), scaleFactor(1.0f)
{
	std::vector<glm::vec3> geoVertices;
	std::vector<glm::vec3> geoNormals;
	std::vector<GLuint> geoIndices;
	glm::vec3 geoColor = Constants::defaultColor();

	std::vector<glm::vec3> vnVertices;
	std::vector<GLuint> vnIndices;
	unsigned int vnCounter = 0;

	std::vector<glm::vec3> fnVertices;
	std::vector<GLuint> fnIndices;
	unsigned int fnCounter = 0;

	std::vector<glm::vec3> bVertices;
	std::vector<GLuint> bIndices;

	//std::vector<glm::vec3> bounds;

	for (auto iter = mesh.vertices.begin(); iter != mesh.vertices.end(); ++iter) {
		// Geometry vertices and normals
		geoVertices.push_back( (*iter)->position );
		geoNormals.push_back( (*iter)->normal );
		
		// Vertex normals
		vnVertices.push_back( (*iter)->position );
		vnIndices.push_back(vnCounter++);
		vnVertices.push_back( (*iter)->position + (*iter)->normal );
		vnIndices.push_back(vnCounter++);
	}

	nVertexNormalIndices = vnCounter;

	for (auto iter = mesh.faces.begin(); iter != mesh.faces.end(); ++iter) {
		Face *face = (*iter);
		HalfEdge *e = face->edge->next;

		// Face normal (first vertex)
		fnVertices.push_back(face->edge->vert->position);
		fnIndices.push_back(fnCounter++);
		fnVertices.push_back(face->edge->vert->position + face->normal);
		fnIndices.push_back(fnCounter++);

		while (e->next != face->edge) {
			// Geometry indices
			geoIndices.push_back(e->vert->id - 1);
			geoIndices.push_back(e->next->vert->id - 1);
			geoIndices.push_back(face->edge->vert->id - 1);

			// Face normals
			fnVertices.push_back(e->vert->position);
			fnIndices.push_back(fnCounter++);
			fnVertices.push_back(e->vert->position + face->normal);
			fnIndices.push_back(fnCounter++);

			e = e->next;
		}

		// Face normal (last vertex)
		fnVertices.push_back(e->vert->position);
		fnIndices.push_back(fnCounter++);
		fnVertices.push_back(e->vert->position + face->normal);
		fnIndices.push_back(fnCounter++);

	}

	nFaceNormalIndices = fnCounter;

	// Bounding box
	Bounds b = mesh.getBounds();
	bVertices.push_back({ b.min_x, b.min_y, b.min_z });
	bVertices.push_back({ b.min_x, b.min_y, b.max_z });
	bVertices.push_back({ b.min_x, b.max_y, b.min_z });
	bVertices.push_back({ b.min_x, b.max_y, b.max_z });
	bVertices.push_back({ b.max_x, b.min_y, b.min_z });
	bVertices.push_back({ b.max_x, b.min_y, b.max_z });
	bVertices.push_back({ b.max_x, b.max_y, b.min_z });
	bVertices.push_back({ b.max_x, b.max_y, b.max_z });

	bIndices.push_back(0), bIndices.push_back(1);
	bIndices.push_back(2), bIndices.push_back(3);
	bIndices.push_back(4), bIndices.push_back(5);
	bIndices.push_back(6), bIndices.push_back(7);

	bIndices.push_back(0), bIndices.push_back(2);
	bIndices.push_back(1), bIndices.push_back(3);
	bIndices.push_back(4), bIndices.push_back(6);
	bIndices.push_back(5), bIndices.push_back(7);

	bIndices.push_back(0), bIndices.push_back(4);
	bIndices.push_back(1), bIndices.push_back(5);
	bIndices.push_back(2), bIndices.push_back(6);
	bIndices.push_back(3), bIndices.push_back(7);


	geometry = new VertexArrayObject(geoShader, true, GL_TRIANGLES);
	geometry->init(geoVertices, geoNormals, geoColor, geoIndices);

	vNormals = new VertexArrayObject(normalShader, false, GL_LINES);
	vNormals->setVertices(vnVertices);
	vNormals->setIndices(vnIndices);
	vNormals->setUniColor(vertexNormalColor);

	fNormals = new VertexArrayObject(normalShader, false, GL_LINES);
	fNormals->setVertices(fnVertices);
	fNormals->setIndices(fnIndices);
	fNormals->setUniColor(faceNormalColor);

	bounds = new VertexArrayObject(normalShader, false, GL_LINES);
	bounds->setVertices(bVertices);
	bounds->setIndices(bIndices);
	bounds->setUniColor(boundsColor);

}

GeometryObject::~GeometryObject()
{
	delete geometry;
	delete vNormals;
	delete fNormals;
	delete bounds;

	geometry = nullptr;
	vNormals = nullptr;
	fNormals = nullptr;
	bounds   = nullptr;
}

void GeometryObject::render(glm::mat4x4 model, glm::mat4x4 view, glm::mat4x4 projection)
{
	model = model * glm::scale( glm::mat4(1.0f), glm::vec3(scaleFactor));
	if (geometry && showGeo) {
		geometry->render(model, view, projection);
	}

	if (vNormals && showVN) {
		vNormals->render(model, view, projection);
	}

	if (fNormals && showFN) {
		fNormals->render(model, view, projection);
	}

	if (bounds && showBox) {
		bounds->render(model, view, projection);
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
	if (geometry) {
		geometry->setShader(shader);
	}
}

void GeometryObject::SetNormalShader(cg::GLSLProgram & shader)
{
	if (vNormals) {
		vNormals->setShader(shader);
	}

	if (fNormals) {
		fNormals->setShader(shader);
	}

	if (bounds) {
		bounds->setShader(shader);
	}
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

void GeometryObject::setGeometryColor(glm::vec3 color)
{
	geometry->setUniColor(color);
}

void GeometryObject::setVertexNormalColor(glm::vec3 color)
{
	vertexNormalColor = color;
	if (vNormals) {
		vNormals->setUniColor(vertexNormalColor);
	}
}

void GeometryObject::setFaceNormalColor(glm::vec3 color)
{
	faceNormalColor = color;
	if (fNormals) {
		fNormals->setUniColor(faceNormalColor);
	}
}

void GeometryObject::setBoundsColor(glm::vec3 color)
{
	boundsColor = color;
	if (bounds) {
		bounds->setUniColor(boundsColor);
	}
}

void GeometryObject::setMaterial(glm::vec3 material, float shininess)
{
	geometry->setMaterial(material, shininess);
}

void GeometryObject::useLighting(bool value)
{
	geometry->useLighting(value);
}

void GeometryObject::scale(float value)
{
	scaleFactor = value;
}
