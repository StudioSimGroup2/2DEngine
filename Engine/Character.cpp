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
		mPosition.X += (mSpeed * mSpeedModifier) * deltaTime;
	}
	if (mMovingLeft)
	{
		mPosition.X -= (mSpeed * mSpeedModifier)* deltaTime;
	}
	if (mMovingUp)
	{
		mPosition.Y += (mSpeed * mSpeedModifier)* deltaTime;
	}
	if (mMovingDown)
	{
		mPosition.Y -= (mSpeed * mSpeedModifier)* deltaTime;
	}
}

void Character::Render(ID3D11DeviceContext* devCon)
{
	PhysicsObject::Render(devCon);
}
