#ifndef CGRAPH_H
#define CGRAPH_H

#include "CEntityVertex.h"
#include "CEntityEdge.h"
#include <map>

class CEngine;

class CGraph
{
public:
	CGraph(CEngine* engine);
	~CGraph();

	void AddVertex(CEntityVertex* vertex);
	void AddEdge(CEntityEdge* edge);
	std::vector<CEntityEdge*> AStar(CEntityVertex* start, CEntityVertex* goal);
	int heuristicCostEstimate(CEntityVertex* start, CEntityVertex* goal);
	std::vector<CEntityEdge*> reconstructPath(std::map<CEntityVertex*, CEntityVertex*> cameFrom, CEntityVertex* current);
	int distanceBetween(CEntityVertex* start, CEntityVertex* next);

	std::vector<CEntityVertex*> vertexList;
	std::vector<CEntityEdge*> edgeList;

	CEntityVertex* baseVertex;
private:
	CEngine* engine;
};

#endif CENTITY_H
