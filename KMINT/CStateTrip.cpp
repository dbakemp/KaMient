#include "CStateTrip.h"
#include "CStateToBase.h"

void CStateTrip::Execute(CEntityImker * imker)
{
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
