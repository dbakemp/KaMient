#ifndef CSTATECOLLECT_H
#define CSTATECOLLECT_H

#include "SDL.h"
#include <vector>
#include "CEntityImker.h"

class CStateCollect : public CState
{
public:
	void Execute(CEntityImker* imker);
};

#endif
