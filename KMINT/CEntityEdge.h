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

	CEntityVertex* vertexA;
	CEntityVertex* vertexB;
private:
	CEngine* engine;
};

#endif
