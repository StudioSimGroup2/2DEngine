#include "GameScreenTest.h"
#include <Sprite.h>
#include "Engine/Renderer/Renderer2D.h"
#include <Engine/Audio/AudioManager.h>

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
	testMap = LevelMap::LoadLevelMap((char*)"Assets/TileMaps/XML_Test.xml");

	Texture* stoneTex = AssetManager::GetInstance()->LoadTexture((char*)"Stone", (char*)"Assets/Textures/Stone.png");

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
				mapItem->AddRendererComponent();

				ThingsToRender.push_back(mapItem);
				break;
			}
			default:
				break;
			}
		}
	}

	vec2f* Position = new vec2f(32, 32);
	TestCharacter = new Character(mDevice, (char*)"Test Character", Position, AssetManager::GetInstance()->LoadTexture((char*)std::string("Mario").c_str(), (char*)"Assets/Textures/Mario.png"));
	TestCharacter->AddRendererComponent();

	AudioManager::GetInstance()->LoadSound("TempBGM", "Assets/Audio/Music/8_bit_peractorum_lofi.wav");
	AudioManager::GetInstance()->LoadSound("TempSFX", "Assets/Audio/SFX/zip.wav");
	AudioManager::GetInstance()->PlaySoundFile("TempBGM", 7.0f, true, true);
}
