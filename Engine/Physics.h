#pragma once

#include <vector>
#include "Common.h"

#define GRAVITY -0.98f
#define FRICTIONCOEF 0.5f

class Physics 
{
public:
	Physics();
	~Physics();
	void Update(float dT);
	void ResetForces();

	void chageGrounded() { mGrounded != mGrounded; };
	void AddThrust();

	
	std::vector<Vector2D> actingForces;

private:
	void UpdateForces(float dT);
	void UpdateAcceleration();

	bool mGrounded = true;
	Vector2D mNetForce;
	Vector2D mNetAcceleration;
	Vector2D mCurrentVelocity;
	float mWeight;

};

