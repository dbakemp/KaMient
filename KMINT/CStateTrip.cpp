#include "CStateTrip.h"
#include "CStateToBase.h"
#include "CEntityPowerup.h"
#include "CGraph.h"
#include "CIntegerHelper.h"

void CStateTrip::Execute(CEntityImker * imker)
{
	if (imker->engine->graph->powerupVertex == nullptr) {
		imker->engine->graph->powerupVertex = imker->engine->graph->vertexList.at(CIntegerHelper::GetRandomIntBetween(0, imker->engine->graph->vertexList.size() - 1));
		imker->engine->powerup->position = imker->engine->graph->powerupVertex->position;
	}

	imker->speedMod = 3;

	imker->WalkTo(imker->nearestBee->GetNearestVertex());

	for (CEntityBee* bee : imker->engine->beeList) {
		if (imker->position.distance_to(bee->position) <= imker->radius && imker->beeCounter < 30) {
			bee->caught = true;
			imker->beeCounter++;
		}
	}

	if (imker->beeCounter >= 30) {
		imker->speedMod = 1;
		imker->ChangeState(new CStateToBase());
	}
}
