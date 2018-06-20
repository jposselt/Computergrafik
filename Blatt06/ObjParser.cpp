#include <sstream>
#include <string>

#include "ObjParser.h"

ObjParser::ObjParser()
{
}

ObjParser::~ObjParser()
{
}

bool ObjParser::load_mesh(const std::string & filename, Mesh & mesh)
{
	std::ifstream input(filename);

	std::string line;
	while (std::getline(input, line))
	{
		if (line[0] == 'v' && line[1] == ' ') {

		}
		else if (line[0] == 'f' && line[1] == ' ') {

		}
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {

		}
	}

	return false;
}
