#ifndef CSTATEGETPOWERUP_H
#define CSTATEGETPOWERUP_H

#include "SDL.h"
#include <vector>
#include "CEntityImker.h"

class CStateGetPowerup : public CState
{
public:
	void Execute(CEntityImker* imker);
private: 
	CEntityVertex* randomVertex = nullptr;
};

#endif
