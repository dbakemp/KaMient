#ifndef CENTITYPOWERUP_H
#define CENTITYPOWERUP_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"
#include "CEntityVertex.h"
#include "CEntityBee.h"
#include "CState.h"

class CEntityPowerup: public CEntity, public IDrawListener
{
public:
	CEntityPowerup(CEngine* engine);
	~CEntityPowerup();

	void Draw(SDL_Renderer* renderer);
	void Update();
	Vec2d position;
private:
	CEngine* engine;
};

#endif
