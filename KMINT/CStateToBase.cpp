#include "CStateToBase.h"
#include "CGraph.h"
#include "CStateCollect.h"

void CStateToBase::Execute(CEntityImker * imker)
{
	imker->WalkTo(imker->engine->graph->baseVertex);

	if (imker->currentVertex == imker->engine->graph->baseVertex) {
		imker->beeCounter = 0;
		imker->ChangeState(new CStateCollect());
	}
}
