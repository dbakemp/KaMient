#ifndef CSTATETRIP_H
#define CSTATETRIP_H

#include "SDL.h"
#include <vector>
#include "CEntityImker.h"

class CStateTrip : public CState
{
public:
	void Execute(CEntityImker* imker);
};

#endif
