#include "GameScreenTest.h"
#include <Sprite.h>
#include "Engine/Renderer/Renderer2D.h"

GameScreenTest::GameScreenTest(Device* Device) : GameScreen(Device)
{
	Initalise();
}

GameScreenTest::~GameScreenTest()
{
	for (auto Thing : ThingsToRender)
	{
		delete Thing;
		Thing = nullptr;
	}
}

void GameScreenTest::Update(float deltaTime)
{
	TestCharacter->Update(deltaTime);
}

void GameScreenTest::Render()
{
	for (auto Thing : ThingsToRender)
	{
		Thing->Draw();
	}

	TestCharacter->Render();
}

void GameScreenTest::Initalise()
{
	testMap = LevelMap::LoadLevelMap((char*)"Resources/TileMaps/XML_Test.xml");

	Texture* stoneTex = AssetManager::GetInstance()->LoadTexture((char*)std::string("Stone").c_str(), (char*)"Textures/stone.png");

	for (int X = 0; X < testMap.size(); X++)
	{
		for (int Y = 0; Y < testMap[0].size(); Y++)
		{
			switch (testMap[X][Y])
			{
			case 0:
			{
				break;
			}
			case 1:
			{
				Sprite* mapItem = new Sprite((char*)std::string("Tile").c_str(), new vec2f(TILEWIDTH * Y, TILEHEIGHT * X), stoneTex);
				mapItem->AddRendererComponent(Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default")));

				ThingsToRender.push_back(mapItem);
				break;
			}
			default:
				break;
			}
		}
	}

	vec2f* Position = new vec2f(32, 32);
	TestCharacter = new Character(mDevice, (char*)"Test Character", Position, AssetManager::GetInstance()->LoadTexture((char*)std::string("Mario").c_str(), (char*)"Textures/mario.png"));
	TestCharacter->AddRendererComponent(Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default")));
}
