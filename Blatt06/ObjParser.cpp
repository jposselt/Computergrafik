#include <sstream>
#include <string>
#include <iostream>
#include <iterator>

#include "ObjParser.h"

using namespace std;

ObjParser::ObjParser()
{
}

ObjParser::~ObjParser()
{
}

bool ObjParser::load_mesh(const string & filename, Mesh & mesh)
{
	std::ifstream input(filename);

	if (!input.good()) {
		cout << "Could not read file." << endl;
		return false;
	}

	std::string line;
	while (input.good()) {
		getline(input, line);
		parse_line(mesh, line);
	}

	cout << "Loaded mesh: " << std::endl
		<< "  " << mesh.verteces.size() << " verteces." << endl
		<< "  " << mesh.edges.size() << " edges." << endl
		<< "  " << mesh.faces.size() << " faces." << endl;
	return true;
}

void ObjParser::parse_line(Mesh & objm, std::string line)
{
	if (line[0] == 'v' && line[1] == ' ') {
		// Line is a verteces
		Vertex *v = new Vertex();

		// Parse vertex position from line
		float x, y, z;
		sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);

		// Set vertex id, position and add to mesh
		v->position = glm::vec3(x, y, z);
		v->id = objm.verteces.size() + 1;
		objm.verteces.push_back(v);
	}
	else if (line[0] == 'f' && line[1] == ' ') {
		// Line is a face
		Face *f = new Face();

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
			e->face = f;

			// Vertex indices for the halfedge
			unsigned int i1 = stoul(tokens[i]);
			unsigned int i2 = stoul(tokens[ (i % (tokens.size() -1)) + 1]);

			// Set halfedge vertex
			e->vert = objm.verteces.at(i1 - 1); // -1: ids not zero-based

			// Set references to the halfedge in the other structures
			// This might be overwriting a previous value, but that's fine
			objm.verteces.at(i1 - 1)->e = e;
			f->edge = e;

			// TODO: connect halfedge pairs (with helper map)

			// Set id and add halfedge to mesh
			e->id = objm.edges.size() + 1;
			objm.edges.push_back(e);

			// Add to edge list
			edgeList.push_back(e);
		}

		// Connect the edges using the edge list
		for (unsigned int i = 0; i < edgeList.size(); i++) {
			edgeList.at(i)->next = edgeList.at( (i+1) % edgeList.size());
		}

		// ...

		// Set id and add face to mesh
		f->id = objm.faces.size() + 1;
		objm.faces.push_back(f);
	}
	else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
		// Line is a normal
	}
}
