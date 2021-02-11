#include "Character.h"

Character::Character(Sprite* sprite, Vector2D Position) : mSprite(sprite), mPosition(Position)
{

}

Character::~Character()
{
}

void Character::Update(float deltaTime)
{
	//Add physcics etc.
	Vector2D Pos = mPosition;

	mSprite->SetPosition(mPosition);
	mSprite->Update(deltaTime);
}

void Character::render(ID3D11DeviceContext* devCon)
{
	mSprite->Render(devCon);
}
