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

	bool loadMesh(const std::string &filename, Mesh &mesh);
private:
	void parseLine(Mesh &objm, std::string line);

	EdgeMap edgeMap;
};

