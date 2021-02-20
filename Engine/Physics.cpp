#include "Physics.h"

Physics::Physics() 
{
	mGrounded = true;

	//Initialize Net Forces
	mNetForce.X = 0.0f;
	mNetForce.Y = 0.0f;

	//Initialize Net Acceleration
	mNetAcceleration.X = 0.0f;
	mNetAcceleration.Y = 0.0f;

	//Initialize Velocity
	mCurrentVelocity.X = 0.0f;
	mCurrentVelocity.Y = 0.0f;

	mWeight = 100.0f;
}

Physics::~Physics()
{

}

void Physics::UpdateForces(float dT)
{
	mCurrentVelocity = mCurrentVelocity + (mNetAcceleration * dT);

	if (mGrounded)
	{
		mNetForce.X += (mCurrentVelocity.X * -FRICTIONCOEF);
	}
	else
	{
		mNetForce.Y += (mWeight * GRAVITY);
	}
}

void Physics::UpdateAcceleration()
{
	mNetAcceleration = mNetForce / mWeight;
}

void Physics::ResetForces()
{
	actingForces.clear();
	mNetForce.X = 0.0f;
	mNetForce.Y = 0.0f;
}

void Physics::AddThrust(Vector2D thrust)
{
	mThrust = mThrust + thrust;
}

void Physics::Update(float dT)
{
	for (int i = 0; i < actingForces.size(); i++)
	{
		mNetForce.X += actingForces[i].X;
		mNetForce.Y += actingForces[i].Y;
	}

	UpdateAcceleration();
	UpdateForces(dT);
}
