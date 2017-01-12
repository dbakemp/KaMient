#ifndef CENTITYIMKER_H
#define CENTITYIMKER_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"
#include "CEntityVertex.h"
#include "CEntityBee.h"
#include "CState.h"

class CState;

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
	CEntityVertex* nextVertex;
	CEntityEdge* currentEdge;
	std::vector<CEntityEdge*> currentPath;
	void ChangeState(CState* state);
	void WalkTo(CEntityVertex* vertex);
	bool walking;
	int radius;
	int ticks;
	int radiusTicks;
	CEngine* engine;
	CEntityBee* nearestBee;
	CState* currentState;
	int beeCounter;
	int speedMod;

	double chancePowerup;
	double chanceBase;
	double chancePanic;
private:
};

#endif
