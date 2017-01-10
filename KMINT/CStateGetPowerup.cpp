#include "CStateGetPowerup.h"
#include "CGraph.h"
#include "CStateToBase.h"
#include "CIntegerHelper.h"
#include "CStateTrip.h"

void CStateGetPowerup::Execute(CEntityImker * imker)
{
	if (randomVertex == nullptr) {
		randomVertex = imker->engine->graph->vertexList.at(CIntegerHelper::GetRandomIntBetween(0, imker->engine->graph->vertexList.size() - 1));
	}

	imker->WalkTo(randomVertex);

	if (imker->currentVertex == randomVertex) {
		imker->beeCounter = 0;
		imker->ChangeState(new CStateTrip());
	}
}
