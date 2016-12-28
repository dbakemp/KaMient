#include "CEntityMapBackground.h"
#include "CDrawManager.h"
#include "CTextureManager.h"

CEntityMapBackground::CEntityMapBackground(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Tile)
{
	this->texture = engine->textureManager->GetTexture("Images/map.png");
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);

	this->engine = engine;	
}

CEntityMapBackground::~CEntityMapBackground()
{
}

void CEntityMapBackground::Draw(SDL_Renderer * renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void CEntityMapBackground::Update()
{
}
