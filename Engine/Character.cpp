#include "Character.h"
Character::Character(ID3D11Device* device, const wchar_t* name, Vector2D Position) : PhysicsObject(device, name, Position)
{
	mSpeed = 20;
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
		PhysicsObject::mPhysics->AddThrust(Vector2D (1,0) * (mSpeed * mSpeedModifier));
	}
	if (mMovingLeft)
	{
		PhysicsObject::mPhysics->AddThrust(Vector2D(-1, 0) * (mSpeed * mSpeedModifier));
	}
	if (mMovingUp)
	{
		PhysicsObject::mPhysics->AddThrust(Vector2D(0, -1) * (mSpeed * mSpeedModifier));
	}
	if (mMovingDown)
	{
		PhysicsObject::mPhysics->AddThrust(Vector2D(0, 1) * (mSpeed * mSpeedModifier));
	}

	PhysicsObject::Update(deltaTime);

}

void Character::Render(ID3D11DeviceContext* devCon)
{
	PhysicsObject::Render(devCon);
}
