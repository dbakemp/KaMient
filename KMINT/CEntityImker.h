#ifndef CENTITYIMKER_H
#define CENTITYIMKER_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"
#include "CEntityVertex.h"
#include "CEntityBee.h"

class CEntityImker : public CEntity, public IDrawListener
{
public:
	CEntityImker(CEngine* engine);
	~CEntityImker();
	CEntityBee* GetNearestBee();

	void Draw(SDL_Renderer* renderer);
	void Update();
	Vec2d position;
	CEntityVertex* currentVertex;
	std::vector<CEntityEdge*> places;
private:
	CEngine* engine;
	CEntityBee* nearestBee;
	
};

#endif
