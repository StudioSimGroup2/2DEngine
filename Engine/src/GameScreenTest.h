#pragma once
#include "GameScreen.h"



class GameScreenTest : public GameScreen
{
public:
	GameScreenTest(D3D11Device* Device);
	~GameScreenTest();

	void Update(float deltaTime);
	void Render();
	void Initalise();
private:

	TileMap testMap;
	Character* TestCharacter;

	
};


