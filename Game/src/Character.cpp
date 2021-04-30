#include "Character.h"
#include "Engine/Input/InputManager.h"

Character::Character(Device* dev, char* name, vec2f* position, Texture* tex)
		:PhysicsObject(dev, position, name,  tex)
{
	mSpeed = 200;
	mSpeedModifier = 1;

	mDirection = vec2f(0.0f);

	InputManager::GetInstance()->BindCommandToButton(KEY_W, [&] {mDirection.y = -1.0f; });
	InputManager::GetInstance()->BindCommandToButton(KEY_A, [&] {mDirection.x = -1.0f; });
	InputManager::GetInstance()->BindCommandToButton(KEY_S, [&] {mDirection.y = 1.0f; });
	InputManager::GetInstance()->BindCommandToButton(KEY_D, [&] {mDirection.x = 1.0f; });
}

Character::~Character()
= default;

void Character::Update(float deltaTime)
{
	//deltaTime /= 1000;
	//Add physcics etc.

	PhysicsObject::mPhysics->AddThrust(mDirection * (mSpeed * mSpeedModifier));

	mDirection = vec2f(0.0f);

	PhysicsObject::Update(deltaTime);

}

void Character::Render()
{
	PhysicsObject::Render();
}

void Character::DoAttack()
{
}