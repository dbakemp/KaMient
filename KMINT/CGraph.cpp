#include "CGraph.h"

CGraph::CGraph(CEngine * engine)
{
	this->engine = engine;
}

CGraph::~CGraph()
{
}

void CGraph::AddVertex(CEntityVertex * vertex)
{
	vertexList.push_back(vertex);
}

void CGraph::AddEdge(CEntityEdge * edge)
{
	edgeList.push_back(edge);
}
