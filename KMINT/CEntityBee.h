#ifndef CENTITYBEE_H
#define CENTITYBEE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"
#include "CEntityVertex.h"

class CEntityBee : public CEntity, public IDrawListener, public IInputListener
{
public:
	CEntityBee(CEngine* engine);
	~CEntityBee();

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	CEntityVertex* GetNearestVertex();

	Vec2d GetAlignment();
	Vec2d GetSeparation();
	Vec2d GetSeparationKeeper();
	Vec2d GetCohesion();

	Vec2d position;
	Vec2d velocity;
	Vec2d acceleration;
	float r;
	float maxforce;
	float maxspeed;

	float imkerSense;
	float imkerForce;

	double DistanceTo(CEntityBee* agent);
	CEntityVertex* nearestVertex;
	bool caught;
	int ticks;
private:
	CEngine* engine;
	int neighbourCount;
	Vec2d v;
};

#endif
