#include "Physics.h"

Physics::Physics(Vector2D* position) : mPosition(position)
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

	mMass = 1.0f;
	mWeight = mMass * GRAVITY;
}

Physics::~Physics()
{

}

void Physics::UpdateForces(float dT)
{
	
	//Calculate new velocity using the formula v = u + at
	mCurrentVelocity = mCurrentVelocity + (mNetAcceleration * dT);

	if (mCurrentVelocity.X > 200.0f)
		mCurrentVelocity.X = 200.0f;
	if (mCurrentVelocity.X < -200.0f)
		mCurrentVelocity.X = -200.0f;

	ResetForces();

	if (mGrounded)
	{
		// When grounded, apply frictional force equal to the current velocity
		// multiplied by a frictional coefficient
		mNetForce.X += (mCurrentVelocity.X * -FRICTIONCOEF);
	}
	else
	{
		//When not grounded, apply gravitational force equal to
		//the weight of the character multiplied by gravity
		mNetForce.Y += mWeight;
	}
}

void Physics::UpdateAcceleration()
{
	// Calculate acceleration
	mNetAcceleration = mNetForce / mWeight;
}

void Physics::ResetForces()
{
	//Clear the acting force buffer, and reset net forces to 0
	actingForces.clear();
	mNetForce.X = 0.0f;
	mNetForce.Y = 0.0f;
}

void Physics::AddThrust(Vector2D thrust)
{
	actingForces.push_back(thrust);

}

void Physics::Update(float dT)
{
	//For each force currently being applied, add it to the total net force
	for (int i = 0; i < actingForces.size(); i++)
	{
		mNetForce.X += actingForces[i].X;
		mNetForce.Y += actingForces[i].Y;
	}

	UpdateAcceleration();
	UpdateForces(dT);

	//Calculate new position using formula s = ut + 1/2at^2
	mPosition->X = mPosition->X + (mCurrentVelocity.X * dT) + (mNetAcceleration.X * 0.5f * (dT * dT));
	mPosition->Y = mPosition->Y + (mCurrentVelocity.Y * dT) + (mNetAcceleration.Y * 0.5f * (dT * dT));
}
