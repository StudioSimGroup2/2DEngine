#pragma once

#include "Sprite.h"
#include "Common.h"
#include "PhysicsObject.h"

class Character : public PhysicsObject
{
public:
	Character(Device* dev, const std::string& name, const std::string& path, vec2f* position);
	~Character();
	void Update(float deltaTime);
	void Render();
	void DoAttack();

	void setMovingUp(bool State) { mMovingUp = State; }
	void setMovingRight(bool State) { mMovingRight = State; }
	void setMovingDown(bool State) { mMovingDown = State; }
	void setMovingLeft(bool State) { mMovingLeft = State; }

private:
	Vector2D mPosition;

	bool mMovingUp = false;
	bool mMovingRight = false;
	bool mMovingDown = false;
	bool mMovingLeft = false;

	float mSpeed;
	float mSpeedModifier;
};