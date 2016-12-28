#include "CEntityVertex.h"
#include "CDrawManager.h"
#include "CEntityBee.h"

CEntityVertex::CEntityVertex(CEngine * engine, int x, int y) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Tile+2)
{
	dstrect.w = 10;
	dstrect.h = 10;
	dstrect.x = x;
	dstrect.y = y;
	position = { (float)x, (float)y };
	this->engine = engine;
}

CEntityVertex::~CEntityVertex()
{
}

void CEntityVertex::Draw(SDL_Renderer * renderer)
{
	SDL_Rect rect = { dstrect.x- dstrect.w/2 , dstrect.y- dstrect.h/2, dstrect.w, dstrect.h};
	SDL_RenderFillRect(renderer, &rect);
}

void CEntityVertex::Update()
{
	neighbourCount = 0;
	for (CEntityBee* other : engine->beeList) {
		float d = position.distance_to(other->position);
		if ((d > 0) && (d < 30)) {
			neighbourCount++;
		}
	}
}
