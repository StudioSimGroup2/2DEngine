#include "Physics.h"

Physics::Physics()
{
	grounded = true;

	//Initialize Net Forces
	netForce.X = 0.0f;
	netForce.Y = 0.0f;

	//Initialize Net Acceleration
	netAcceleration.X = 0.0f;
	netAcceleration.Y = 0.0f;

	//Initialize Velocity
	currentVelocity.X = 0.0f;
	currentVelocity.Y = 0.0f;

	weight = 100.0f;
}

Physics::~Physics()
{

}

void Physics::UpdateForces()
{
	currentVelocity = currentVelocity + (netAcceleration * deltaTime);

	if (grounded)
	{
		netForce.X += (currentVelocity.X * -FRICTIONCOEF);
	}
	else
	{
		netForce.Y += (weight * GRAVITY);
	}


}

void Physics::UpdateAcceleration()
{
	netAcceleration = netForce / weight;
}

void Physics::ResetForces()
{
	actingForces.clear();
	netForce.X = 0.0f;
	netForce.Y = 0.0f;
}

void Physics::Update()
{
	for (int i = 0; i < actingForces.size(); i++)
	{
		netForce.X += actingForces[i].X;
		netForce.Y += actingForces[i].Y;
	}

	UpdateAcceleration();
	UpdateForces();
}
