#pragma once

#include <fstream>
#include "Mesh.h"

class ObjParser
{
public:
	ObjParser();
	~ObjParser();

	bool load_mesh(const std::string &filename, Mesh &mesh);
};

