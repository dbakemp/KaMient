#include "CEntity.h"
#include "CEngine.h"

CEntity::CEntity(CEngine* engine): IEntityListener(engine)
{
}

CEntity::~CEntity()
{
}

void CEntity::Update()
{
}

void CEntity::SetType(Type type)
{
	this->type = type;
}

CEntity::Type CEntity::GetType()
{
	return type;
}