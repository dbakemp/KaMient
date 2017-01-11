#include "CGraph.h"
#include "limits.h"
#include <set>
#include <map>
#include <vector>
#include <algorithm>

struct MapSort
{
	MapSort(std::map<CEntityVertex*, int> fScore)
	{
		this->fScore = fScore;
	}

	bool operator() (CEntityVertex* vertexA, CEntityVertex* vertexB) {
		if (fScore.find(vertexA)->second < fScore.find(vertexB)->second)
			return -1;
		if (fScore.find(vertexB)->second < fScore.find(vertexA)->second)
			return 1;
		return 0;
	}

	std::map<CEntityVertex*, int> fScore;
};

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

std::vector<CEntityEdge*> CGraph::AStar(CEntityVertex* start, CEntityVertex* goal)
{
	CEntityVertex* current = nullptr;
	std::vector<CEntityVertex*> openSet, closedSet;
	openSet.push_back(start);

	std::map<CEntityVertex*, CEntityVertex*> cameFrom;
	std::map<CEntityVertex*, int> gScore;
	gScore.insert(std::pair<CEntityVertex*, int>(start, 0));

	std::map<CEntityVertex*, int> fScore;
	for (CEntityVertex* vertex : vertexList) {
		fScore.insert(std::pair<CEntityVertex*, int>(vertex, INT_MAX));
	}
	fScore.insert(std::pair<CEntityVertex*, int>(start, heuristicCostEstimate(start, goal)));

	while (!openSet.empty()) {
		current = openSet.at(0);
		if (current == goal) {
			return reconstructPath(cameFrom, goal);
		}

		openSet.erase(openSet.begin() + 0);
		closedSet.push_back(current);

		for (CEntityEdge* edge : current->edges) {
			CEntityVertex* neighbor = edge->GetNeighbor(current);
			
			if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
				continue;
			}

			int tenativeGScore = gScore.find(current)->second + distanceBetween(current, neighbor);

			if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
				openSet.push_back(neighbor);
			} else {
				continue;
			}

			cameFrom.insert(std::pair<CEntityVertex*, CEntityVertex*>(neighbor, current));
			gScore.insert(std::pair<CEntityVertex*, int>(neighbor, tenativeGScore));
			int estimatedFScore = gScore.find(neighbor)->second + heuristicCostEstimate(neighbor, goal);
			fScore.insert(std::pair<CEntityVertex*, int>(neighbor, estimatedFScore));

			std::sort(openSet.begin(), openSet.end(), MapSort(fScore));
		}

	}


	return std::vector<CEntityEdge*>();
}

int CGraph::heuristicCostEstimate(CEntityVertex * start, CEntityVertex * goal)
{
	return 1;
}

std::vector<CEntityEdge*> CGraph::reconstructPath(std::map<CEntityVertex*, CEntityVertex*> cameFrom, CEntityVertex * current)
{
	std::vector<CEntityEdge*> totalPath;

	while (current != NULL) {
		CEntityVertex* previous = current;
		if (cameFrom.find(current) == cameFrom.end()) {
			current = NULL;
		}
		else {
			current = cameFrom.find(current)->second;
		}
		if (current != NULL) {
			CEntityEdge* edge = current->GetEdge(previous);
			totalPath.push_back(edge);
		}
	}

	std::reverse(totalPath.begin(), totalPath.end());
	return totalPath;
}

int CGraph::distanceBetween(CEntityVertex * start, CEntityVertex * next)
{
	for (CEntityEdge* edge : start->edges) {
		if (edge->vertexB == next) {
			return edge->cost;
		}
		return INT_MAX;
	}
}
