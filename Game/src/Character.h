#pragma once

#include "Sprite.h"
#include "Common.h"
#include "PhysicsObject.h"

class Character : public PhysicsObject
{
public:
	Character(Device* dev, char* name, vec2f* position, Texture* tex);
	~Character();
	void Update(float deltaTime);
	void Render();
	void DoAttack();

private:
	Vector2D mPosition;
	vec2f mDirection;

	float mSpeed;
	float mSpeedModifier;
};