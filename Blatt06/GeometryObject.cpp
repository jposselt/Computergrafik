#include <glm/gtc/matrix_transform.hpp>
#include "GeometryObject.h"
#include "Constants.h"

GeometryObject::GeometryObject(VertexArrayObject* geometry, VertexArrayObject* vNormals, VertexArrayObject* fNormals, VertexArrayObject* bounds)
	: geometry(geometry), vNormals(vNormals), fNormals(fNormals), bounds(bounds),
	showGeo(true), showVN(false), showFN(false), showBox(false),
	vertexNormalColor(Constants::defaultVNColor()), faceNormalColor(Constants::defaultFNColor()), boundsColor(Constants::defaultColor()), scaleFactor(1.0f)
{
	initOffset = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
	initScale = glm::mat4(1.0f);
}

GeometryObject::GeometryObject(VertexArrayObject * geometry)
	: GeometryObject(geometry, nullptr, nullptr, nullptr)
{
}

GeometryObject::GeometryObject(Mesh& mesh, cg::GLSLProgram& geoShader, cg::GLSLProgram& normalShader)
	: showGeo(true), showVN(false), showFN(false), showBox(false),
	vertexNormalColor(Constants::defaultVNColor()), faceNormalColor(Constants::defaultFNColor()), boundsColor(Constants::defaultColor()), scaleFactor(1.0f)
{
	std::vector<glm::vec3> geoVertices;
	std::vector<glm::vec3> geoNormals;
	std::vector<glm::vec2> texCoords;
	std::vector<GLuint> geoIndices;
	glm::vec3 geoColor = Constants::defaultColor();
	unsigned int geoCounter = 0;

	std::vector<glm::vec3> vnVertices;
	std::vector<GLuint> vnIndices;
	unsigned int vnCounter = 0;

	std::vector<glm::vec3> fnVertices;
	std::vector<GLuint> fnIndices;
	unsigned int fnCounter = 0;

	std::vector<glm::vec3> bVertices;
	std::vector<GLuint> bIndices;

	for (auto iter = mesh.faces.begin(); iter != mesh.faces.end(); ++iter) {
		Face *face = (*iter);
		HalfEdge *e = face->edge;

		unsigned int iStart = geoVertices.size();
		unsigned int iNext = iStart + 1;

		while (e->next != face->edge) {
			// Add position and normal of the current vertex
			geoVertices.push_back( e->vert->position );
			geoNormals.push_back( e->normal );
			texCoords.push_back( e->uv );

			// Add indices for triangle fan
			if ( e->next->next != face->edge ) {
				geoIndices.push_back(iNext++);
				geoIndices.push_back(iNext);
				geoIndices.push_back(iStart);
			}

			// Add start and endpoint of vertex normal to list
			vnVertices.push_back(e->vert->position);
			vnIndices.push_back(vnCounter++);
			vnVertices.push_back(e->vert->position + e->normal);
			vnIndices.push_back(vnCounter++);

			// Add start and endpoint of face normal to list
			fnVertices.push_back(e->vert->position);
			fnIndices.push_back(fnCounter++);
			fnVertices.push_back(e->vert->position + face->normal);
			fnIndices.push_back(fnCounter++);

			e = e->next;
		}

		// Add position and normal of the last vertex
		geoVertices.push_back(e->vert->position);
		geoNormals.push_back(e->normal);
		texCoords.push_back(e->uv);

		// Add start and endpoint of last vertex normal to list
		vnVertices.push_back(e->vert->position);
		vnIndices.push_back(vnCounter++);
		vnVertices.push_back(e->vert->position + e->normal);
		vnIndices.push_back(vnCounter++);

		// Add start and endpoint of last face normal to list
		fnVertices.push_back(e->vert->position);
		fnIndices.push_back(fnCounter++);
		fnVertices.push_back(e->vert->position + face->normal);
		fnIndices.push_back(fnCounter++);

	}

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

	// Initial offset and scale
	initOffset = glm::translate(glm::mat4(1.0f), glm::vec3(-(b.min_x + b.max_x) / 2.0f, -(b.min_y + b.max_y) / 2.0f, -(b.min_z + b.max_z) / 2.0f));
	initScale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f / std::fmaxf(b.max_x - b.min_x, std::fmaxf(b.max_y - b.min_y, b.max_z - b.min_z))));

	// Create vertex array objects
	geometry = new VertexArrayObject(geoShader, true, GL_TRIANGLES);
	geometry->init(geoVertices, geoNormals, geoColor, texCoords, geoIndices);

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
	model = model * glm::scale( glm::mat4(1.0f), glm::vec3(scaleFactor)) * initScale * initOffset;
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
