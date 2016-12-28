#include "CEntityBee.h"
#include "CDrawManager.h"
#include "CTextureManager.h"
#include "CIntegerHelper.h"
#include <math.h>

CEntityBee::CEntityBee(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IInputListener(engine)
{
	this->engine = engine;
	this->SetType(Type::BEE);
	this->texture = engine->textureManager->GetTexture("Images/bee.png");
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);

	acceleration = { 0, 0 };
	position = { (float)CIntegerHelper::GetRandomIntBetween(0, 600) , (float)CIntegerHelper::GetRandomIntBetween(0, 600) };
	float angle = CIntegerHelper::GetRandomIntBetween(0, M_PI*2);
	velocity = {cos(angle), sin(angle)};
	r = dstrect.w/2;
	maxspeed = 2;
	maxforce = 0.03;
}

CEntityBee::~CEntityBee()
{
}

void CEntityBee::Draw(SDL_Renderer * renderer)
{
	dstrect.x = position.x;
	dstrect.y = position.y;
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void CEntityBee::Update()
{
	Vec2d sep = GetSeparation();   // Separation
	Vec2d ali = GetAlignment();      // Alignment
	Vec2d coh = GetCohesion();   // Cohesion
									 // Arbitrarily weight these forces
	sep = sep * 1.5f;
	ali = ali * 1.0f;
	coh = coh * 1.0f;

	// Add the force vectors to acceleration
	acceleration = acceleration + sep;
	acceleration = acceleration + ali;
	acceleration = acceleration + coh;

	velocity = velocity + acceleration;
	// Limit speed
	if (velocity.length() > maxspeed) {
		int i = 0;
	}
	velocity = velocity.limit(maxspeed);
	position = position + velocity;
	// Reset accelertion to 0 each cycle
	acceleration = { 0, 0 };

	if (position.x < -r) position.x = engine->windowWidth + r;
	if (position.y < -r) position.y = engine->windowHeight + r;
	if (position.x > engine->windowWidth + r) position.x = -r;
	if (position.y > engine->windowHeight + r) position.y = -r;
}

void CEntityBee::Input(SDL_Event * event)
{
}

Vec2d CEntityBee::GetAlignment()
{
	float neighbordist = 50;
	Vec2d sum = { 0, 0 };
	int count = 0;
	for (CEntityBee* other : engine->beeList) {
		float d = position.distance_to(other->position);
		if ((d > 0) && (d < neighbordist)) {
			sum = sum + other->velocity;
			count++;
		}
	}
	if (count > 0) {
		sum = sum / (float)count;
		// First two lines of code below could be condensed with new PVector setMag() method
		// Not using this method until Processing.js catches up
		// sum.setMag(maxspeed);

		// Implement Reynolds: Steering = Desired - Velocity
		sum = sum.norm();
		sum = sum * maxspeed;
		Vec2d steer = sum - velocity;
		steer = steer.limit(maxforce);
		return steer;
	}
	else {
		return{ 0, 0 };
	}
}

Vec2d CEntityBee::GetSeparation()
{
	float desiredseparation = 25.0f;
	Vec2d steer = { 0, 0 };
	int count = 0;
	// For every boid in the system, check if it's too close
	for (CEntityBee* other : engine->beeList) {
		float d = position.distance_to(other->position);
		// If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
		if ((d > 0) && (d < desiredseparation)) {
			// Calculate vector pointing away from neighbor
			Vec2d diff = position - other->position;
			diff = diff.norm();
			diff = diff / d;        // Weight by distance
			steer = steer + diff;
			count++;            // Keep track of how many
		}
	}
	// Average -- divide by how many
	if (count > 0) {
		steer = steer / (float)count;
	}

	// As long as the vector is greater than 0
	if (steer.length() > 0) {
		// First two lines of code below could be condensed with new PVector setMag() method
		// Not using this method until Processing.js catches up
		// steer.setMag(maxspeed);

		// Implement Reynolds: Steering = Desired - Velocity
		steer = steer.norm();
		steer = steer * maxspeed;
		steer = steer - velocity;
		steer = steer.limit(maxforce);
	}
	return steer;
}

Vec2d CEntityBee::GetCohesion()
{
	float neighbordist = 50;
	Vec2d sum = { 0, 0 };
	int count = 0;
	for (CEntityBee* other : engine->beeList) {
		float d = position.distance_to(other->position);
		if ((d > 0) && (d < neighbordist)) {
			sum = sum + other->position;
			count++;
		}
	}
	if (count > 0) {
		sum = sum / count;
		Vec2d desired = sum - position;  // A vector pointing from the position to the target
														  // Scale to maximum speed
		desired = desired.norm();
		desired = desired * maxspeed;

		// Above two lines of code below could be condensed with new PVector setMag() method
		// Not using this method until Processing.js catches up
		// desired.setMag(maxspeed);

		// Steering = Desired minus Velocity
		Vec2d steer = desired - velocity;
		steer = steer.limit(maxforce);
		return steer;
	}
	else {
		return{ 0, 0 };
	}
}

double CEntityBee::DistanceTo(CEntityBee* agent)
{
	int x = (this->dstrect.x + (this->dstrect.w / 2)) - (agent->dstrect.x + (agent->dstrect.w / 2));
	int y = (this->dstrect.y + (this->dstrect.h / 2)) - (agent->dstrect.y + (agent->dstrect.h / 2));
	double hyp = std::hypot(x, y);

	return hyp;
}
