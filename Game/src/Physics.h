#pragma once

#include <vector>
#include "Common.h"
#include <Utils/Math.h>

#define GRAVITY 0.98f
#define FRICTIONCOEF 0.5f

class Physics
{
public:
	Physics(vec2f* position);
	~Physics();
	void Update(float dT);
	void ResetForces();

	void chageGrounded() { mGrounded != mGrounded; };
	void AddThrust(vec2f thrust);

	std::vector<vec2f> actingForces;

private:
	void UpdateForces(float dT);
	void UpdateAcceleration();

	bool mGrounded = true;
	vec2f mNetForce;
	vec2f mThrust;
	vec2f mNetAcceleration;
	vec2f mCurrentVelocity;
	vec2f* mPosition;
	float mMass;
	float mWeight;

};