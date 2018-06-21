#pragma once
#include "Mesh.h"

class MeshAnalyser
{
public:
	MeshAnalyser();
	~MeshAnalyser();

	static void analyse(Mesh &mesh);

private:

	typedef struct MeshStatistics {
		unsigned int nVertices;
		unsigned int nFaces;
		unsigned int nHalfEdges;
		std::map<unsigned int, unsigned int> faceValence;
		std::map<unsigned int, unsigned int> vertexValence;
	} MeshStatistics;

	static void analyseVertices(Mesh &mesh, MeshStatistics &statistics);
	static void analyseFaces(Mesh &mesh, MeshStatistics &statistics);
	static void analyseEdges(Mesh &mesh, MeshStatistics &statistics);
	static void printStatistics(MeshStatistics &statistics);
};

