#ifndef CENTITYVERTEX_H
#define CENTITYVERTEX_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "vector2d.hpp"

class CEntityEdge;

class CEntityVertex : public CEntity, public IDrawListener
{
public:
	CEntityVertex(CEngine* engine, int x, int y);
	~CEntityVertex();

	void Draw(SDL_Renderer* renderer);
	void Update();
	int GetScore();
	int neighbourCount;
	int score;
	Vec2d position;
	std::vector<CEntityEdge*> edges;
	CEntityEdge* GetEdge(CEntityVertex* previous);
private:
	CEngine* engine;

	int weight = 0;
};

#endif
