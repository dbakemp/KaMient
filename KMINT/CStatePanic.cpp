#include "CStatePanic.h"
#include "CGraph.h"
#include "CStateToBase.h"
#include "CIntegerHelper.h"

void CStatePanic::Execute(CEntityImker * imker)
{
	if (randomVertex == nullptr) {
		randomVertex = imker->engine->graph->vertexList.at(CIntegerHelper::GetRandomIntBetween(0, imker->engine->graph->vertexList.size()-1));
	}

	imker->WalkTo(randomVertex);

	if (imker->currentVertex == randomVertex) {
		randomVertex = nullptr;
	}

	loseCounter++;

	if (loseCounter >= 15) {
		loseCounter = 0;
		imker->engine->caughtBees[0]->caught = false;
		imker->engine->caughtBees[0]->position = imker->position;
		imker->beeCounter -= 1;
	}

	if (imker->beeCounter <= 0) {
		imker->ChangeState(new CStateToBase());
	}
}