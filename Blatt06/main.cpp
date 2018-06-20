#include "Mesh.h"
#include "ObjParser.h"

int main(int argc, char** argv)
{
	Mesh m;
	ObjParser parser;

	parser.load_mesh("A4_testcube2_mitSpitze.obj", m);
	return 0;
}