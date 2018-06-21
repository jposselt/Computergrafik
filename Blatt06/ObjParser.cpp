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
bool ObjParser::load_mesh(const string & filename, Mesh & mesh)
{
	edgeMap.clear();
	ifstream input(filename);

	if (!input.good()) {
		cout << "Could not read file." << endl;
		return false;
	}

	string line;
	while (input.good()) {
		getline(input, line);
		parse_line(mesh, line);
	}

	cout << "Loaded mesh: " << endl
		<< "  " << mesh.vertices.size() << " verteces." << endl
		<< "  " << mesh.edges.size() << " edges." << endl
		<< "  " << mesh.faces.size() << " faces." << endl;
	return true;
}

/// <summary>
/// Parses a line from the obj file.
/// </summary>
/// <param name="objm">Halfedge mesh in which parsed information is stored.</param>
/// <param name="line">The line to parse.</param>
void ObjParser::parse_line(Mesh & objm, string line)
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

			// Vertex indices for the halfedge
			unsigned int i1 = stoul(tokens[i]);
			unsigned int i2 = stoul(tokens[ (i % (tokens.size() -1)) + 1]);

			// Set halfedge vertex
			e->vert = objm.vertices.at(i1 - 1); // -1: ids not zero-based

			// Set references to the halfedge in the other structures
			// This might be overwriting a previous value, but that's fine
			objm.vertices.at(i1 - 1)->e = e;
			f->edge = e;

			// Connect halfedge pairs (with helper map)
			EdgeKey pairKey = make_pair(i2, i1);
			EdgeMap::iterator it = edgeMap.find(pairKey);
			if ( it != edgeMap.end() ) {
				e->pair = it->second;
				it->second->pair = e;
				edgeMap.erase(it);
			}
			else {
				edgeMap.insert( make_pair( make_pair(i1, i2), e) );
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
	else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
		// Line is a normal
	}
}
