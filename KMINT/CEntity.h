#ifndef CENTITY_H
#define CENTITY_H

#include "IEntityListener.h"

class CEngine;


class CEntity: public IEntityListener
{
public:

	CEntity(CEngine* engine);
	~CEntity();
	void Update();

	enum class Type
	{
		BEE
	};

	void SetType(Type type);
	Type GetType();
	float xPos, yPos;
	float xVel, yVel;
	float xAcc, yAcc;
	int height, width;
private:
	Type type;
};

#endif CENTITY_H
