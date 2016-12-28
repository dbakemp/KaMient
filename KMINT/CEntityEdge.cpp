#include "CEntityEdge.h"
#include "CDrawManager.h"

CEntityEdge::CEntityEdge(CEngine * engine, CEntityVertex * vertexA, CEntityVertex * vertexB) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Tile+1)
{
	this->vertexA = vertexA;
	this->vertexB = vertexB;
	this->engine = engine;
}

CEntityEdge::~CEntityEdge()
{
}

void CEntityEdge::Draw(SDL_Renderer * renderer)
{
	SDL_RenderDrawLine(renderer, vertexA->dstrect.x, vertexA->dstrect.y, vertexB->dstrect.x, vertexB->dstrect.y);
}

void CEntityEdge::Update()
{
}
