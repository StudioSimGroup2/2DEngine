#include "PhysicsComp.h"
#include "Entities/GameObject.h"

Engine::PhysicsComp::PhysicsComp()
{
}

Engine::PhysicsComp::~PhysicsComp()
{

}

void Engine::PhysicsComp::Init()
{
	mType = COMPONENT_PHYSICS;
	//Initialize Net Forces
	mNetForce.x = 0.0f;
	mNetForce.y = 0.0f;

	//Initialize Velocity
	mCurrentVelocity.x = 0.0f;
	mCurrentVelocity.y = 0.0f;

	mMass = 1.0f;
}

void Engine::PhysicsComp::UpdateForces(float dT, vec2f accel)
{
	//Calculate new velocity using the formula v = u + at
	mCurrentVelocity = mCurrentVelocity + (accel * dT);
	mWeight = mMass * mGravity;
	ResetForces();

	if (mGrounded)
	{
		// When grounded, apply frictional force equal to the current velocity
		// multiplied by a frictional coefficient
		mCurrentVelocity.y = 0;
		mNetForce.x += (mCurrentVelocity.x * -mFriction);
	}
	else
	{
		//When not grounded, apply gravitational force equal to
		//the weight of the character multiplied by gravity
		mNetForce.y += mWeight;
	}
}

void Engine::PhysicsComp::Update()
{
	float dkfjdsf = float(0.016);
	Update(dkfjdsf);
}

void Engine::PhysicsComp::Render()
{
}

void Engine::PhysicsComp::Start()
{
}

void Engine::PhysicsComp::InternalUpdate()
{
	ResetForces();
	mCurrentVelocity.x = 0.0f;
	mCurrentVelocity.y = 0.0f;
}

void Engine::PhysicsComp::InternalRender()
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

	vec2f acceleration = vec2f(mNetForce.x / mWeight, mNetForce.y / mWeight);
	UpdateForces(dT, acceleration);

	//Calculate new position using formula s = ut + 1/2at^2
	vec2f position = mParent->GetComponent<TransformComp>()->GetPosition();

	position += (mCurrentVelocity * dT) + (acceleration * 0.5f * (dT * dT));
	
	mParent->GetComponent<TransformComp>()->SetPosition(position);
}
