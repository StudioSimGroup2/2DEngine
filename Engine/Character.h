#pragma once
#include "Sprite.h"
#include "Common.h"

class Character
{
public:
	Character(Sprite* sprite, Vector2D Position, float Speed);
	Character(Sprite* sprite, Vector2D Position, float Speed, float SpeedMod);
	~Character();
	void Update(float deltaTime);
	void render(ID3D11DeviceContext* devCon);

	void setMovingUp(bool State) { mMovingUp = State; }
	void setMovingRight(bool State) { mMovingRight = State; }
	void setMovingDown(bool State) { mMovingDown = State; }
	void setMovingLeft(bool State) { mMovingLeft = State; }

private:
	Sprite* mSprite;
	Vector2D mPosition;

	bool mMovingUp = false;
	bool mMovingRight = false;
	bool mMovingDown = false;
	bool mMovingLeft = false;

	float mSpeed;
	float mSpeedModifier;
};

