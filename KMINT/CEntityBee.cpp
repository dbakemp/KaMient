#include "CEntityBee.h"
#include "CDrawManager.h"
#include "CTextureManager.h"
#include "CIntegerHelper.h"
#include "CEntityImker.h"
#include "CGraph.h"
#include <math.h>

CEntityBee::CEntityBee(CEngine * engine, std::string bitstring) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IInputListener(engine)
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
	maxforce = 0.03;

	genetics = new BeeGenetics();

	if (bitstring == "") {
		genetics->maxspeed = ((float)CIntegerHelper::GetRandomIntBetween(15, 30) / 10);
		genetics->imkerForce = ((float)CIntegerHelper::GetRandomIntBetween(0, 30) / 10);
		genetics->imkerSense = ((float)CIntegerHelper::GetRandomIntBetween(100, 1500) / 10);
	}
	else
	{
		genetics->imkerForce = (double)CIntegerHelper::BitStringToInt(bitstring.substr(0, 5))/10;
		genetics->imkerSense = (double)CIntegerHelper::BitStringToInt(bitstring.substr(5, 11))/10;
		genetics->maxspeed = (double)CIntegerHelper::BitStringToInt(bitstring.substr(16, 5))/10;
	}

	caught = false;
	ticks = 0;
}

CEntityBee::~CEntityBee()
{
}

void CEntityBee::Draw(SDL_Renderer * renderer)
{
	if (!caught) {
		dstrect.x = position.x - dstrect.w / 2;
		dstrect.y = position.y - dstrect.h / 2;
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	}
}

void CEntityBee::Update()
{
	if (!caught) {
		Vec2d sep = GetSeparation();   // Separation
		Vec2d sepk = GetSeparationKeeper();   // Separation
		Vec2d ali = GetAlignment();      // Alignment
		Vec2d coh = GetCohesion();   // Cohesion
									 // Arbitrarily weight these forces
		sep = sep * 1.5f;			 // Arbitrarily weight these forces
		sepk = sepk * genetics->imkerForce;
		ali = ali * 1.0f;
		coh = coh * 1.0f;

		// Add the force vectors to acceleration
		acceleration = acceleration + sep;
		acceleration = acceleration + sepk;
		acceleration = acceleration + ali;
		acceleration = acceleration + coh;

		velocity = velocity + acceleration;
		// Limit speed
		if (velocity.length() > genetics->maxspeed) {
			int i = 0;
		}
		velocity = velocity.limit(genetics->maxspeed);
		position = position + velocity;
		// Reset accelertion to 0 each cycle
		acceleration = { 0, 0 };

		if (position.x < -r) position.x = engine->windowWidth + r;
		if (position.y < -r) position.y = engine->windowHeight + r;
		if (position.x > engine->windowWidth + r) position.x = -r;
		if (position.y > engine->windowHeight + r) position.y = -r;

		ticks++;
	}
}

void CEntityBee::Input(SDL_Event * event)
{
}

CEntityVertex* CEntityBee::GetNearestVertex()
{
	nearestVertex = nullptr;
	float closest = NULL;
	for (CEntityVertex* other : engine->graph->vertexList) {
		float d = position.distance_to(other->position);
		if (d < closest || closest == NULL) {
			nearestVertex = other;
			closest = d;
		}
	}

	return nearestVertex;
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
		sum = sum * genetics->maxspeed;
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
		steer = steer * genetics->maxspeed;
		steer = steer - velocity;
		steer = steer.limit(maxforce);
	}
	return steer;
}

Vec2d CEntityBee::GetSeparationKeeper()
{
	float desiredseparation = 25.0f;
	Vec2d steer = { 0, 0 };
	int count = 0;
	// For every boid in the system, check if it's too close
	float d = position.distance_to(engine->imker->position);
	// If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
	if ((d > 0) && (d < genetics->imkerSense)) {
		// Calculate vector pointing away from neighbor
		Vec2d diff = position - engine->imker->position;
		diff = diff.norm();
		diff = diff / d;        // Weight by distance
		steer = steer + diff;
		count++;            // Keep track of how many
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
		steer = steer;
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
		desired = desired * genetics->maxspeed;

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

std::string CEntityBee::GetBeeGeneticString()
{
	std::string imkerForceBit = std::bitset<5>(genetics->imkerForce*10).to_string();
	std::string imkerSenseBit = std::bitset<11>(genetics->imkerSense*10).to_string();
	std::string maxSpeedBit = std::bitset<5>(genetics->maxspeed*10).to_string();

	return imkerForceBit + imkerSenseBit + maxSpeedBit;
}
