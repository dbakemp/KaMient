#include "CEntityImker.h"
#include "CDrawManager.h"
#include "CTextureManager.h" 
#include "CEntityBee.h"
#include "CEntityVertex.h"
#include "CGraph.h"

CEntityImker::CEntityImker(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object - 1)
{
	this->texture = engine->textureManager->GetTexture("Images/beekeeper.png");
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);

	currentVertex = engine->graph->baseVertex;
	position = { currentVertex->position.x, currentVertex->position.y };

	this->engine = engine;
}

CEntityImker::~CEntityImker()
{
}

void CEntityImker::Draw(SDL_Renderer * renderer)
{
	dstrect.x = position.x-dstrect.w/2;
	dstrect.y = position.y-dstrect.h/2;
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void CEntityImker::Update()
{
	CEntityBee* nearestBee = GetNearestBee();
	if (nearestBee != nullptr) {
		CEntityVertex* nearestVertex = nearestBee->GetNearestVertex();
	}
}

CEntityBee* CEntityImker::GetNearestBee()
{
	nearestBee = nullptr;
	float closest = NULL;
	for (CEntityBee* other : engine->beeList) {
		float d = position.distance_to(other->position);
		if (d < closest || closest == NULL) {
			nearestBee = other;
			closest = d;
		}
	}

	return nearestBee;
}
