#include "GeometryObject.h"
#include "Constants.h"

GeometryObject::GeometryObject(VertexArrayObject* geometry, VertexArrayObject* vNormals, VertexArrayObject* fNormals, VertexArrayObject* bounds)
	: geometry(geometry), vNormals(vNormals), fNormals(fNormals), bounds(bounds),
	showGeo(true), showVN(false), showFN(false), showBox(false)
{
}

GeometryObject::GeometryObject(VertexArrayObject * geometry)
	: GeometryObject(geometry, nullptr, nullptr, nullptr)
{
}

GeometryObject::GeometryObject(Mesh mesh, cg::GLSLProgram& geoShader, cg::GLSLProgram& normalShader)
	: showGeo(true), showVN(false), showFN(false), showBox(false)
{
	std::vector<glm::vec3> geoVertices;
	std::vector<glm::vec3> geoNormals;
	std::vector<GLuint> geoIndices;
	glm::vec3 geoColor = Constants::defaultColor();

	std::vector<glm::vec3> vnVertices;
	std::vector<GLuint> vnIndices;
	unsigned int vnCounter = 0;

	//std::vector<glm::vec3> fNormals;
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

	for (auto iter = mesh.faces.begin(); iter != mesh.faces.end(); ++iter) {
		Face *face = (*iter);
		HalfEdge *e = face->edge->next;

		while (e->next != face->edge) {
			geoIndices.push_back(e->vert->id - 1);
			geoIndices.push_back(e->next->vert->id - 1);
			geoIndices.push_back(face->edge->vert->id - 1);
			e = e->next;
		}

		// ...
	}

	geometry = new VertexArrayObject(geoShader, true, GL_TRIANGLES);
	geometry->init(geoVertices, geoNormals, geoColor, geoIndices);

	vNormals = new VertexArrayObject(normalShader, false, GL_LINES);
	vNormals->setVertices(vnVertices);
	vNormals->setIndices(vnIndices);
	vNormals->setUniColor(Constants::defaultVNColor(), vnVertices.size());

	fNormals = new VertexArrayObject(normalShader, false, GL_LINES);
	// ...

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
