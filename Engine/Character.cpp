#include "Character.h"
Character::Character(Sprite* sprite, Vector2D Position, float Speed) : mSprite(sprite), mPosition(Position), mSpeed(Speed)
{
	mSpeedModifier = 1;
}

Character::Character(Sprite* sprite, Vector2D Position, float Speed, float SpeedMod) : mSprite(sprite), mPosition(Position), mSpeed(Speed), mSpeedModifier(SpeedMod)
{

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



	mSprite->SetPosition(mPosition);
	mSprite->Update(deltaTime);
}

void Character::render(ID3D11DeviceContext* devCon)
{
	mSprite->Render(devCon);
}
