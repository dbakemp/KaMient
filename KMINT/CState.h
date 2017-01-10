#ifndef CSTATE_H
#define CSTATE_H

#include "SDL.h"
#include <vector>
#include "CEntityImker.h"

class CState
{
public:
	virtual void Execute(CEntityImker* imker) = 0;
};

#endif
