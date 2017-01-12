#include "CEntityPowerup.h"
#include "CDrawManager.h"
#include "CTextureManager.h"

CEntityPowerup::CEntityPowerup(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object)
{
	this->engine = engine;
	this->texture = engine->textureManager->GetTexture("Images/banana.gif");
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
}

CEntityPowerup::~CEntityPowerup()
{
}

void CEntityPowerup::Draw(SDL_Renderer * renderer)
{
	dstrect.x = position.x - dstrect.w / 2;
	dstrect.y = position.y - dstrect.h / 2;
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void CEntityPowerup::Update()
{
}
