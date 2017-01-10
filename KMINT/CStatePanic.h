#ifndef CSTATEPANIC_H
#define CSTATEPANIC_H

#include "SDL.h"
#include <vector>
#include "CEntityImker.h"
#include "CEntityVertex.h"

class CStatePanic : public CState
{
public:
	void Execute(CEntityImker* imker);
private:
	CEntityVertex* randomVertex = nullptr;
	int loseCounter = 0;;
};

#endif
