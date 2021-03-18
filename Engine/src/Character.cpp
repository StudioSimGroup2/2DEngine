#include "Character.h"

Character::Character(Device* dev, const std::string& name, const std::string& path, vec2f* position) : PhysicsObject(dev, name, path, position)
{
	mSpeed = 200;
	mSpeedModifier = 1;
}

Character::~Character()
{
}

void Character::Update(float deltaTime)
{
	deltaTime /= 1000;
	//Add physcics etc.

	if (mMovingRight)
	{
		PhysicsObject::mPhysics->AddThrust(vec2f(1, 0) * (mSpeed * mSpeedModifier));
	}
	if (mMovingLeft)
	{
		PhysicsObject::mPhysics->AddThrust(vec2f(-1, 0) * (mSpeed * mSpeedModifier));
	}
	if (mMovingUp)
	{
		PhysicsObject::mPhysics->AddThrust(vec2f(0, -1) * (mSpeed * mSpeedModifier));
	}
	if (mMovingDown)
	{
		PhysicsObject::mPhysics->AddThrust(vec2f(0, 1) * (mSpeed * mSpeedModifier));
	}

	PhysicsObject::Update(deltaTime);

}

void Character::Render()
{
	PhysicsObject::Render();
}

void Character::DoAttack()
{
}