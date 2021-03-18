#pragma once
#include "GameScreen.h"
class GameScreenTest : public GameScreen
{
public:
	GameScreenTest(ID3D11DeviceContext* Context, ID3D11Device* Device);
	~GameScreenTest();

	void Update(float deltaTime);
	void Render();
	void Initalise();
private:

	std::vector<Sprite*> ThingsToRender;
	Sprite* mTempSprite;
	//Remove
	Sprite* TestSprite;
	Character* TestCharacter;
	TileMap testMap;
};


