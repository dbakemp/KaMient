#ifndef CGRAPH_H
#define CGRAPH_H

#include "CEntityVertex.h"
#include "CEntityEdge.h"

class CEngine;

class CGraph
{
public:
	CGraph(CEngine* engine);
	~CGraph();

	void AddVertex(CEntityVertex* vertex);
	void AddEdge(CEntityEdge* edge);

	std::vector<CEntityVertex*> vertexList;
	std::vector<CEntityEdge*> edgeList;
private:
	CEngine* engine;
};

#endif CENTITY_H
