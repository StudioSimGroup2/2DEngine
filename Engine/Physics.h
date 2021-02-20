#pragma once

#include "Sprite.h"
#include <vector>

#define GRAVITY -0.98f
#define FRICTIONCOEF 0.5f

class Physics
{
public:
	Physics();
	~Physics();

	bool grounded = true;
	Vector2D netForce;
	Vector2D netAcceleration;
	Vector2D currentVelocity;
	float weight;

	std::vector<Vector2D> actingForces;

private:

	void UpdateForces(float dT);
	void UpdateAcceleration();
	void ResetForces();

	void Update(float dT);

};

