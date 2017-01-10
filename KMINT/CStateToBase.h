#ifndef CSTATETOBASE_H
#define CSTATETOBASE_H

#include "SDL.h"
#include <vector>
#include "CEntityImker.h"

class CStateToBase : public CState
{
public:
	void Execute(CEntityImker* imker);
};

#endif
