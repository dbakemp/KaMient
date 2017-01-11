#ifndef CENTITYEDGE_H
#define CENTITYEDGE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"
#include "CEntityVertex.h"

class CEntityEdge : public CEntity, public IDrawListener
{
public:
	CEntityEdge(CEngine* engine, CEntityVertex* vertexA, CEntityVertex* vertexB);
	~CEntityEdge();

	void Draw(SDL_Renderer* renderer);
	void Update();
	CEntityVertex* GetNeighbor(CEntityVertex* current);

	CEntityVertex* vertexA;
	CEntityVertex* vertexB;
	int cost = 0;

private:
	CEngine* engine;

};

#endif
