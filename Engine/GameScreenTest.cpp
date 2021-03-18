#include "GameScreenTest.h"

GameScreenTest::GameScreenTest(ID3D11DeviceContext* Context, ID3D11Device* Device) : GameScreen(Context, Device)
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
	if (GetAsyncKeyState(0x27)) //Right arrow
	{
		TestCharacter->setMovingRight(true);
	}
	else
	{
		TestCharacter->setMovingRight(false);
	}

	if (GetAsyncKeyState(0x25)) //Left arrow
	{
		TestCharacter->setMovingLeft(true);
	}
	else
	{
		TestCharacter->setMovingLeft(false);
	}

	TestCharacter->Update(deltaTime);
}

void GameScreenTest::Render()
{
	for (auto Thing : ThingsToRender)
	{
		Thing->Render(mContext);
	}
	TestCharacter->Render(mContext);
}

void GameScreenTest::Initalise()
{
	testMap = LevelMap::LoadLevelMap((char*)"TinyXML/XML_Test.xml");
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
				Vector2D* Position = new Vector2D(Y * TILEWIDTH, X * TILEHEIGHT);
				Sprite* MapItem = new Sprite(mDevice, L"Textures/stone.dds", Position);
				ThingsToRender.push_back(MapItem);
				break;
			}
			default:
				break;
			}
		}
	}

	Vector2D* Position = new Vector2D(32, 32);
	TestCharacter = new Character(mDevice, L"Textures/Mario.dds", Position);
}
