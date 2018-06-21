#include "Mesh.h"
#include "ObjParser.h"
#include "MeshAnalyser.h"

int main(int argc, char** argv)
{
	Mesh m;
	ObjParser parser;

	parser.loadMesh("A4_testcube2_mitSpitze.obj", m);
	MeshAnalyser::analyse(m);

	return 0;
}