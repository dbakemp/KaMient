#include "CStateGetPowerup.h"
#include "CGraph.h"
#include "CStateToBase.h"
#include "CIntegerHelper.h"
#include "CStateTrip.h"
#include "CEntityPowerup.h"

void CStateGetPowerup::Execute(CEntityImker * imker)
{
	imker->WalkTo(imker->engine->graph->powerupVertex);

	if (imker->currentVertex == imker->engine->graph->powerupVertex) {
		imker->engine->graph->powerupVertex = nullptr;
		imker->beeCounter = 0;
		imker->ChangeState(new CStateTrip());
	}
}
