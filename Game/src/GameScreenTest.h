#pragma once

#include "GameScreen.h"
#include "Character.h"
#include <Sprite.h>

class GameScreenTest : public GameScreen
{
public:
	explicit GameScreenTest(Device* Device);
	~GameScreenTest() override;

	void Update(float deltaTime) override;
	void Render() override;
	void Init();
private:

	//std::vector<Sprite*> ThingsToRender;
	////Remove
	//Sprite* TestSprite;
	//Character* TestCharacter;
	//TileMap testMap;
};


