#pragma once

#include <vector>
#include "Common.h"



#define GRAVITY 0.98f
#define FRICTIONCOEF 0.5f

class Physics 
{
public:
	Physics(Vector2D* position);
	~Physics();
	void Update(float dT);
	void ResetForces();

	void chageGrounded() { mGrounded != mGrounded; };
	void AddThrust(Vector2D thrust);
	
	std::vector<Vector2D> actingForces;

private:
	void UpdateForces(float dT);
	void UpdateAcceleration();

	bool mGrounded = true;
	Vector2D mNetForce;
	Vector2D mThrust;
	Vector2D mNetAcceleration;
	Vector2D mCurrentVelocity;
	Vector2D* mPosition;
	float mMass;
	float mWeight;

};

