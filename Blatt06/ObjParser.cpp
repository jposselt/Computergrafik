#include <sstream>
#include <string>
#include <iostream>
#include <iterator>

#include "ObjParser.h"

using namespace std;

ObjParser::ObjParser()
{
}

/// <summary>
/// Finalizes an instance of the <see cref="ObjParser"/> class.
/// </summary>
ObjParser::~ObjParser()
{
}

/// <summary>
/// Creates a hafledge mesh from an obj file
/// </summary>
/// <param name="filename">Path ot the obj file</param>
/// <param name="mesh">Output Halfedge mesh</param>
/// <returns></returns>
bool ObjParser::loadMesh(const string & filename, Mesh & mesh)
{
	edgeMap.clear();
	vNormals.clear();
	tCoord.clear();
	ifstream input(filename);

	if (!input.good()) {
		cout << "Could not read file." << endl;
		return false;
	}

	string line;
	while (input.good()) {
		getline(input, line);
		parseLine(mesh, line);
	}

	cout << "Loaded mesh: " << endl
		<< "  " << mesh.vertices.size() << " vertices." << endl
		<< "  " << mesh.edges.size() << " edges." << endl
		<< "  " << mesh.faces.size() << " faces." << endl;
	return true;
}

/// <summary>
/// Parses a line from the obj file.
/// </summary>
/// <param name="objm">Halfedge mesh in which parsed information is stored.</param>
/// <param name="line">The line to parse.</param>
void ObjParser::parseLine(Mesh & objm, string line)
{
	if (line[0] == 'v' && line[1] == ' ') {
		// Line is a verteces
		Vertex *v = new Vertex();

		// Parse vertex position from line
		float x, y, z;
		sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);

		// Set vertex id, position and add to mesh
		v->position = glm::vec3(x, y, z);
		v->id = objm.vertices.size() + 1;
		objm.vertices.push_back(v);
	}
	else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
		// Parse normal components from line
		float x, y, z;
		sscanf_s(line.c_str(), "vn %f %f %f", &x, &y, &z);

		// Add normal to list
		vNormals.push_back(glm::vec3(x, y, z));
	}
	else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
		// Parse texture coordinates from line
		float x, y;
		sscanf_s(line.c_str(), "vt %f %f", &x, &y);

		// Add texture coordinate vector to list
		tCoord.push_back(glm::vec2(x, y));
	}
	else if (line[0] == 'f' && line[1] == ' ') {
		// Line is a face
		Face *f = new Face();
		f->id = objm.faces.size() + 1;

		/* Tokenize the line */
		istringstream tokenizer(line);
		vector<string> tokens;
		copy(istream_iterator<string>(tokenizer),
			istream_iterator<string>(),
			back_inserter<vector<string> >(tokens));

		// List of edges for this face
		vector<HalfEdge*> edgeList;

		// Iterate over face halfedges
		for (unsigned int i = 1; i < tokens.size(); i++) {
			HalfEdge *e = new HalfEdge();
			e->id = objm.edges.size() + 1;
			e->face = f;

			// Indices (vertex, texture, normal)
			unsigned int v1, vt1, vn1;
			unsigned int v2, vt2, vn2;
			
			if ( sscanf_s(tokens[i].c_str(), "%d/%d/%d", &v1, &vt1, &vn1) == 3 ) {
				sscanf_s(tokens[(i % (tokens.size() - 1)) + 1].c_str(), "%d/%d/%d", &v2, &vt2, &vn2);
				e->normal = vNormals[vn1 - 1];
				e->uv = tCoord[vt1 - 1];
			}
			else if ( sscanf_s(tokens[i].c_str(), "%d//%d", &v1, &vn1) == 2 ) {
				sscanf_s(tokens[(i % (tokens.size() - 1)) + 1].c_str(), "%d//%d", &v2, &vn2);
				e->normal = vNormals[vn1 -1];
			}
			else if ( sscanf_s(tokens[i].c_str(), "%d/%d", &v1, &vt1) == 2 ) {
				sscanf_s(tokens[(i % (tokens.size() - 1)) + 1].c_str(), "%d/%d", &v2, &vt2);
				e->uv = tCoord[vt1 - 1];
			}
			else if ( sscanf_s(tokens[i].c_str(), "%d", &v1) ==  1 ) {
				sscanf_s(tokens[(i % (tokens.size() - 1)) + 1].c_str(), "%d", &v2);
			}
			else {
				cout << "Could not parse token " << tokens[i] << " in line: " << line  << endl;
			}

			// Set halfedge vertex
			e->vert = objm.vertices.at(v1 - 1); // -1: ids not zero-based

			// Set references to the halfedge in the other structures
			// This might be overwriting a previous value, but that's fine
			objm.vertices.at(v1 - 1)->edge = e;
			f->edge = e;

			// Connect halfedge pairs (with helper map)
			EdgeKey pairKey = make_pair(v2, v1);
			EdgeMap::iterator it = edgeMap.find(pairKey);
			if ( it != edgeMap.end() ) {
				e->pair = it->second;
				it->second->pair = e;
				edgeMap.erase(it);
			}
			else {
				edgeMap.insert( make_pair( make_pair(v1, v2), e) );
			}

			// Add halfedge to mesh
			objm.edges.push_back(e);

			// Add to edge list
			edgeList.push_back(e);
		}

		// Connect the edges using the edge list
		for (unsigned int i = 0; i < edgeList.size(); i++) {
			edgeList.at(i)->next = edgeList.at( (i+1) % edgeList.size());
		}

		// Add face to mesh
		objm.faces.push_back(f);
	}
}
