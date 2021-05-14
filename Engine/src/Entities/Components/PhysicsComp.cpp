#include "PhysicsComp.h"
#include "Entities/GameObject.h"

Engine::PhysicsComp::PhysicsComp() : Component()
{
	Init();
	mGrounded;

	
}

Engine::PhysicsComp::~PhysicsComp()
{

}

void Engine::PhysicsComp::Init()
{
	mType = "Physics";
	//Initialize Net Forces
	mNetForce.x = 0.0f;
	mNetForce.y = 0.0f;

	//Initialize Net Acceleration
	mNetAcceleration.x = 0.0f;
	mNetAcceleration.y = 0.0f;

	//Initialize Velocity
	mCurrentVelocity.x = 0.0f;
	mCurrentVelocity.y = 0.0f;

	mMass = 1.0f;
}

void Engine::PhysicsComp::UpdateForces(float dT)
{
	//Calculate new velocity using the formula v = u + at
	mCurrentVelocity = mCurrentVelocity + (mNetAcceleration * dT);
	mWeight = mMass * mGravity;
	ResetForces();

	if (mGrounded)
	{
		// When grounded, apply frictional force equal to the current velocity
		// multiplied by a frictional coefficient
		mNetForce.x += (mCurrentVelocity.x * -mFriction);
	}
	else
	{
		//When not grounded, apply gravitational force equal to
		//the weight of the character multiplied by gravity
		mNetForce.y += mWeight;
	}
}

void Engine::PhysicsComp::UpdateAcceleration()
{
	// Calculate acceleration
	mNetAcceleration.x = mNetForce.x / mWeight;
	mNetAcceleration.y = mNetForce.y / mWeight;
}

void Engine::PhysicsComp::Update()
{
	float dkfjdsf = float(0.016);
	Update(dkfjdsf);
}

void Engine::PhysicsComp::Render()
{
}

void Engine::PhysicsComp::ResetForces()
{
	//Clear the acting force buffer, and reset net forces to 0
	actingForces.clear();
	mNetForce.x = 0.0f;
	mNetForce.y = 0.0f;
}

void Engine::PhysicsComp::AddThrust(vec2f thrust)
{
	actingForces.push_back(thrust);
}

void Engine::PhysicsComp::Update(float dT)
{
	//For each force currently being applied, add it to the total net force
	for (int i = 0; i < actingForces.size(); i++)
	{
		mNetForce.x += actingForces[i].x;
		mNetForce.y += actingForces[i].y;
	}

	UpdateAcceleration();
	UpdateForces(dT);

	//Calculate new position using formula s = ut + 1/2at^2
	vec2f position = mParent->GetComponent<TransformComp>()->GetPosition();

	position += (mCurrentVelocity * dT) + (mNetAcceleration * 0.5f * (dT * dT));
	
	mParent->GetComponent<TransformComp>()->SetPosition(position);
	Logger::LogMsg("Test Pos", mParent->GetComponent<TransformComp>()->GetPosition().y);
}
