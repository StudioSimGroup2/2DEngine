#pragma once
#include "GameScreen.h"
#include <Character.h>
#include <Sprite.h>
#include "Backend/D3D11/D3D11Device.h"

class GameScreenTest : public GameScreen
{
public:
	GameScreenTest(D3D11Device* Device);
	~GameScreenTest();

	void Update(float deltaTime);
	void Render();
	void Initalise();
private:

	std::vector<Sprite*> ThingsToRender;
	Sprite* mTempSprite;
	//Remove
	Sprite* TestSprite;
	//Character* TestCharacter;
	TileMap testMap;
};


