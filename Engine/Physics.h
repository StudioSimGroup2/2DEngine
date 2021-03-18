#pragma once

#include <vector>
#include "Common.h"
#include "Collision.h"



#define GRAVITY 0.98f
#define FRICTIONCOEF 0.8f

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

	Vector2D GetVelocity() { return mCurrentVelocity; }
	Vector2D GetAccel() { return mNetAcceleration; }

	Collision collisionBox;

private:
	void UpdateForces(float dT);
	void UpdateAcceleration();

	bool mGrounded;
	Vector2D mNetForce;
	Vector2D mThrust;
	Vector2D mNetAcceleration;
	Vector2D mCurrentVelocity;
	Vector2D* mPosition;
	float mMass;
	float mWeight;

};

