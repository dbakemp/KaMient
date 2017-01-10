#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"
#include <vector>

class CDrawManager;
class CInputManager;
class CEntityManager;
class CTextureManager;
class CEntityBee;
class CEntityImker;
class CGraph;

class CEngine
{
public:
	CEngine();
	~CEngine();
	CDrawManager* drawManager;
	CInputManager* inputManager;
	CEntityManager* entityManager;
	SDL_Window* window;
	SDL_Renderer* renderer;
	CTextureManager* textureManager;
	bool running;
	int windowHeight, windowWidth;
	std::vector<CEntityBee*> beeList;
	std::vector<CEntityBee*> caughtBees;
	CEntityImker* imker;
	CGraph* graph;
private:
	void Tick();
};

#endif
