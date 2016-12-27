#include "SDL.h"
#include "CDrawManager.h"
#include "IDrawListener.h"
#include <algorithm>

void CDrawManager::AddListener(IDrawListener* drawListener, int index)
{
	listeners.push_back(drawListener);
	listenersIndexed[index].push_back(drawListener);
}

void CDrawManager::RemoveListener(IDrawListener* drawListener)
{
	listenersIndexed[drawListener->zIndex].erase(std::remove(listenersIndexed[drawListener->zIndex].begin(), listenersIndexed[drawListener->zIndex].end(), drawListener), listenersIndexed[drawListener->zIndex].end());
	listeners.erase(std::remove(listeners.begin(), listeners.end(), drawListener), listeners.end());
}

void CDrawManager::Tick(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);

	for (int i = 0; i < 25; i++)
	{
		for (IDrawListener* listener : listenersIndexed[i])
		{
			listener->Draw(renderer);
		}
	}

	for (int i = 25; i < 30; i++)
	{
		for (IDrawListener* listener : listenersIndexed[i])
		{
			listener->Draw(renderer);
		}
	}

	SDL_RenderPresent(renderer);
}

void CDrawManager::ChangeZIndex(IDrawListener* drawListener, int index)
{
	listenersIndexed[drawListener->zIndex].erase(std::remove(listenersIndexed[drawListener->zIndex].begin(), listenersIndexed[drawListener->zIndex].end(), drawListener), listenersIndexed[drawListener->zIndex].end());
	listenersIndexed[index].push_back(drawListener);
	drawListener->zIndex = index;
}

void CDrawManager::Clear()
{
	int i = 0;
	for (std::vector<IDrawListener*> listeners : listenersIndexed)
	{
		listenersIndexed[i].erase(listenersIndexed[i].begin(), listenersIndexed[i].end());
		i++;
	}
	listeners.clear();
}

CDrawManager::CDrawManager(CEngine * engine)
{
	this->engine = engine;
}

CDrawManager::~CDrawManager()
{
}
