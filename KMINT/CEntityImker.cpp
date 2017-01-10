#include "CEntityImker.h"
#include "CDrawManager.h"
#include "CTextureManager.h" 
#include "CEntityBee.h"
#include "CEntityVertex.h"
#include "CGraph.h"
#include "SDL2_gfxPrimitives.h"
#include <math.h> 
#include "CStateCollect.h"

CEntityImker::CEntityImker(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object - 1)
{
	this->texture = engine->textureManager->GetTexture("Images/beekeeper.png");
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);

	currentVertex = engine->graph->baseVertex;
	position = { currentVertex->position.x, currentVertex->position.y };

	walking = false;
	radius = 30;
	ticks = 0;
	beeCounter = 0;
	speedMod = 1;
	ChangeState(new CStateCollect());

	chanceBase = 33.3;
	chancePanic = 33.3;
	chancePowerup = 33.3;
	this->engine = engine;
}

CEntityImker::~CEntityImker()
{
}

void CEntityImker::Draw(SDL_Renderer * renderer)
{
	dstrect.x = position.x-dstrect.w/2;
	dstrect.y = position.y-dstrect.h/2;
	aacircleRGBA(renderer, position.x, position.y, radius, 0, 0, 255, 120);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void CEntityImker::Update()
{
	CEntityBee* bee = GetNearestBee();
	if (bee != nullptr) {
		CEntityVertex* nearestVertex = bee->GetNearestVertex();
		if (bee != nearestBee) {
			nearestBee = bee;
		}
	}

	currentState->Execute(this);

	if (radiusTicks == 60) {
		radiusTicks = 0;
		radius += 10;
	}

	ticks++;
	radiusTicks++;
}

void CEntityImker::ChangeState(CState * state)
{
	delete currentState;
	currentState = state;
}

void CEntityImker::WalkTo(CEntityVertex* vertex)
{
	if (!walking && (currentPath.empty() || (currentPath.back()->vertexA != vertex && currentPath.back()->vertexB != vertex))) {
		currentPath = engine->graph->AStar(currentVertex, vertex);
		currentEdge = nullptr;
		nextVertex = nullptr;

		if (currentPath.empty()) {
			return;
		}
	}

	if (!walking) {
		if (currentEdge == nullptr) {
			currentEdge = currentPath[0];
			walking = true;
			nextVertex = currentEdge->GetNeighbor(currentVertex);
		}
		else {
			auto it = std::find(currentPath.begin(), currentPath.end(), currentEdge);
			int index = std::distance(currentPath.begin(), it);
			
			if (index + 1 >= currentPath.size()) {
				walking = false;
				currentPath.clear();
			}
			else {
				currentEdge = currentPath[index + 1];
				walking = true;
				nextVertex = currentEdge->GetNeighbor(currentVertex);
			}
		}
	}

	if (walking) {
		Vec2d vec = (position - nextVertex->position) / (6/speedMod);
		position = position - vec;

		if (position.x > nextVertex->position.x - 4 && position.x < nextVertex->position.x + 4 && position.y > nextVertex->position.y - 4 && position.y < nextVertex->position.y + 4) {
			position = nextVertex->position;
			currentVertex = nextVertex;
			nextVertex = nullptr;
			walking = false;
		}
	}
}

CEntityBee* CEntityImker::GetNearestBee()
{
	CEntityBee* bee = nullptr;
	float closest = NULL;
	for (CEntityBee* other : engine->beeList) {
		float d = position.distance_to(other->position);
		if (d < closest || closest == NULL) {
			bee = other;
			closest = d;
		}
	}

	return bee;
}
