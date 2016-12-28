#include "CEntityImker.h"
#include "CDrawManager.h"
#include "CTextureManager.h" 

CEntityImker::CEntityImker(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object - 1)
{
	this->texture = engine->textureManager->GetTexture("Images/beekeeper.png");
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
	position = { 280, 280 };

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
}
