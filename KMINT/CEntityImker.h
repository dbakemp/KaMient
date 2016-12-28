#ifndef CENTITYIMKER_H
#define CENTITYIMKER_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"
#include "CEntityVertex.h"

class CEntityImker : public CEntity, public IDrawListener
{
public:
	CEntityImker(CEngine* engine);
	~CEntityImker();

	void Draw(SDL_Renderer* renderer);
	void Update();
	Vec2d position;
private:
	CEngine* engine;
};

#endif
