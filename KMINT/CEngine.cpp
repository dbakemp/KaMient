#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CTextureManager.h"
#include "CDebugLogger.h"
#include <time.h>
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

CEngine::CEngine()
{
	windowHeight = 600;
	windowWidth = 600;

	drawManager = new CDrawManager(this);
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	textureManager = new CTextureManager(this);

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Tonnie's Grote Racewereld", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Surface* icon = IMG_Load("Resources/Images/favicon.ico");
	SDL_SetWindowIcon(window, icon);

	Tick();
}

CEngine::~CEngine()
{
	delete entityManager;
	delete drawManager;
	delete inputManager;
	delete textureManager;

	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void CEngine::Tick()
{
	running = true;

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				SDL_Quit();
			}
			inputManager->Tick(&event);
		}

		entityManager->Tick();
		drawManager->Tick(renderer);
	}
}