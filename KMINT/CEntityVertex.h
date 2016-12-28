#ifndef CENTITYVERTEX_H
#define CENTITYVERTEX_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"

class CEntityVertex : public CEntity, public IDrawListener
{
public:
	CEntityVertex(CEngine* engine, int x, int y);
	~CEntityVertex();

	void Draw(SDL_Renderer* renderer);
	void Update();
	int neighbourCount;
	Vec2d position;
private:
	CEngine* engine;
};

#endif
