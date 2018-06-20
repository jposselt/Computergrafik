#include "Mesh.h"

int main(int argc, char** argv)
{
	Vector3f v1(1, 0, 0);
	Vector3f v2(0, 1, 0);
	Vector3f v3 = v1.cross(v2);
	return 0;
}