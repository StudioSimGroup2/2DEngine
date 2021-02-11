#pragma once
#include "Sprite.h"
#include "Common.h"

class Character
{
public:
	Character(Sprite* sprite, Vector2D Position);
	~Character();
	void Update(float deltaTime);
	void render(ID3D11DeviceContext* devCon);
private:
	Sprite* mSprite;
	Vector2D mPosition;

	bool mMovingUp = false;
	bool mMovingRight = false;
	bool mMovingDown = false;
	bool mMovingLeft = false;

};

