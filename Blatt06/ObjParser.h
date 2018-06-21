#pragma once

#include <fstream>
#include <map>
#include "Mesh.h"

typedef std::pair<unsigned int, unsigned int> EdgeKey;
typedef std::map<EdgeKey, HalfEdge*> EdgeMap;

class ObjParser
{
public:
	ObjParser();
	~ObjParser();

	bool load_mesh(const std::string &filename, Mesh &mesh);
private:
	void parse_line(Mesh &objm, std::string line);

	EdgeMap edgeMap;
};

