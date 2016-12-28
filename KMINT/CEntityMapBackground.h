#ifndef CENTITYMAPBACKGROUND_H
#define CENTITYMAPBACKGROUND_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"

class CEntityMapBackground : public CEntity, public IDrawListener
{
public:
	CEntityMapBackground(CEngine* engine);
	~CEntityMapBackground();

	void Draw(SDL_Renderer* renderer);
	void Update();
private:
	CEngine* engine;
};

#endif
