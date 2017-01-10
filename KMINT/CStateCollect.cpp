#include "CStateCollect.h"
#include "CStateToBase.h"
#include "CIntegerHelper.h"
#include "CStatePanic.h"
#include "CStateGetPowerup.h"

void CStateCollect::Execute(CEntityImker* imker)
{
	imker->WalkTo(imker->nearestBee->GetNearestVertex());

	for (CEntityBee* bee : imker->engine->beeList) {
		if (imker->position.distance_to(bee->position) <= imker->radius && imker->beeCounter < 10) {
			bee->caught = true;
			imker->beeCounter++;
		}
	}

	enum stateEnum { base, panic, powerup };

	if (imker->beeCounter >= 10) {
		double random = ((double)CIntegerHelper::GetRandomIntBetween(0, 999)/10);

		const int rows = 3;
		double chances[rows][2] = {
			{ 0, imker->chanceBase },
			{ 1, imker->chancePanic },
			{ 2, imker->chancePowerup },
		};

		int stateInt = 0;

		for (int i = 0; i < rows; i++) {
			double totalChance = 0;
			for (int o = i; o >= 0; o--) {
				totalChance += chances[o][1];
			}
			if (random <= totalChance) {
				stateInt = chances[i][0];
				break;
			}
		}

		switch (stateInt) {
			case base:
				imker->ChangeState(new CStateToBase());
				break;
			case panic:
				imker->ChangeState(new CStatePanic());
				break;
			case powerup:
				imker->ChangeState(new CStateGetPowerup());
				break;
		}
	}
}