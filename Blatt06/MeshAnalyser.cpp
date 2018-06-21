#include <map>
#include <iostream>
#include "MeshAnalyser.h"

using namespace std;

MeshAnalyser::MeshAnalyser()
{
}

MeshAnalyser::~MeshAnalyser()
{
}

void MeshAnalyser::analyse(Mesh & mesh)
{
	cout << endl << "Analysing mesh: " << endl;

	MeshStatistics statistics;
	analyseFaces(mesh, statistics);
	analyseVertices(mesh, statistics);
	analyseEdges(mesh, statistics);

	cout << endl;

	printStatistics(statistics);
}

void MeshAnalyser::analyseVertices(Mesh & mesh, MeshStatistics & statistics)
{
	bool ok = true;
	for (auto iter = mesh.vertices.begin(); iter != mesh.vertices.end(); ++iter) {
		unsigned int count = 0;
		Vertex *vert = (*iter);
		HalfEdge *edge = vert->edge;

		do {
			if (edge->vert != vert) {
				ok = false;
				cout << "Edge " << edge->id << " expected to connect to vertex " << vert->id << " but connects to vertex " << edge->vert->id << endl;
				break;
			}
			count++;
			edge = edge->pair->next;
		} while ( edge != vert->edge );

		map<unsigned int, unsigned int>::iterator it = statistics.vertexValence.find(count);
		if (it == statistics.vertexValence.end()) {
			statistics.vertexValence.insert(pair<unsigned int, unsigned int>(count, 1));
		}
		else {
			it->second += 1;
		}
	}
	statistics.nVertices = mesh.vertices.size();
	
	if (ok) {
		cout << "Vertices OK" << endl;
	}
	else {
		cout << "Vertices ERRORS" << endl;
	}
}

void MeshAnalyser::analyseFaces(Mesh & mesh, MeshStatistics & statistics)
{
	bool ok = true;
	for (auto iter = mesh.faces.begin(); iter != mesh.faces.end(); ++iter) {
		unsigned int count = 0;
		Face *face = (*iter);
		HalfEdge *edge = face->edge;

		do {
			if (edge->face != face) {
				ok = false;
				cout << "Edge " << edge->id << " expected to border on face " << face->id << " but borders on face " << edge->face->id << endl;
				break;
			}
			count++;
			edge = edge->next;
		} while ( (edge != face->edge) );

		map<unsigned int, unsigned int>::iterator it = statistics.faceValence.find(count);
		if (it == statistics.faceValence.end()) {
			statistics.faceValence.insert(pair<unsigned int, unsigned int>(count, 1));
		} else {
			it->second += 1;
		}

	}
	statistics.nFaces = mesh.faces.size();
	
	if (ok) {
		cout << "Faces OK" << endl;
	}
	else {
		cout << "Faces ERRORS" << endl;
	}
}

void MeshAnalyser::analyseEdges(Mesh & mesh, MeshStatistics & statistics)
{
	bool ok = true;
	for (auto iter = mesh.edges.begin(); iter != mesh.edges.end(); ++iter) {
		HalfEdge *e = (*iter);
		if (e->pair == nullptr) {
			cout << "Edge " << e->id << " has no pair" << endl;
			ok = false;
		}
		else if (e->pair->pair != e) {
			cout << "Pair of edge " << e->id << " does not point back to it" << endl;
			ok = false;
		}
	}
	statistics.nHalfEdges = mesh.edges.size();

	if (ok) {
		cout << "Halfedges OK" << endl;
	}
	else {
		cout << "Halfedges ERRORS" << endl;
	}
}

void MeshAnalyser::printStatistics(MeshStatistics & statistics)
{
	cout << "Mesh Statistics: " << endl;

	cout << statistics.nFaces << " faces." << endl;
	for (map<unsigned int, unsigned int>::iterator it = statistics.faceValence.begin(); it != statistics.faceValence.end(); ++it) {
		cout << it->second << " faces with " << it->first << " edges" << endl;
	}
	cout << endl;

	cout << statistics.nVertices << " vertices." << endl;
	for (map<unsigned int, unsigned int>::iterator it = statistics.vertexValence.begin(); it != statistics.vertexValence.end(); ++it) {
		cout << it->second << " vertices with " << it->first << " edges" << endl;
	}
	cout << endl;

	cout << statistics.nHalfEdges << " halfedges." << endl;
}
