#include "GameScreenTest.h"
#include <Sprite.h>



GameScreenTest::GameScreenTest(D3D11Device* Device) : GameScreen(Device)
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

	//-------------------------------------
	//Testing TileMap editing
	if (GetAsyncKeyState(0x61)) // numpad 1
	{
		int x = 0, y = 0;
		LevelMap::EditTile(&testMap, Vector2D(x,y), 1);
		UpdateTileMap(Vector2D(x,y), 1);

	}
	if (GetAsyncKeyState(0x62)) // numpad 2
	{
		int x = 1, y = 0;
		LevelMap::EditTile(&testMap, Vector2D(x, y), 1);
		UpdateTileMap(Vector2D(x, y), 1);

	}
	if (GetAsyncKeyState(0x60)) // numpad 0
	{
		int x = 0, y = 0;
		LevelMap::EditTile(&testMap, Vector2D(x, y), 0);
		UpdateTileMap(Vector2D(x, y), 0);

	}
	//-------------------------------------------

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
	vec2f* Position = new vec2f(32, 32);
	TestCharacter = new Character(mDevice, "Test Character", "Textures/Mario.dds", Position);
	D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
	TestCharacter->AddRendererComponent(re);

	mCharacters.push_back(TestCharacter);

	Sprite* TempSprite = new Sprite(mDevice, "Temp", std::string("Textures/stone.dds"), new vec2f(0,0));
	TempSprite->AddRendererComponent(re);

	ThingsToRender.push_back(TempSprite);

	testMap = LevelMap::LoadLevelMap((char*)"Resources/TileMaps/XML_Test.xml");
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
				UpdateTileMap(Vector2D(X, Y), 1);
				////awkward way of naming sprite but oh well
				//std::string name;
				//char buffer[50];
				//sprintf(buffer, "Tile [ %d %d ]", X, Y);
				//name = buffer;
				////----
				//Sprite* mapItem = new Sprite(mDevice, name, std::string("Textures/stone.dds"), new vec2f(TILEWIDTH * Y, TILEHEIGHT * X));
				//D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
				//mapItem->AddRendererComponent(re);

				//ThingsToRender.push_back(mapItem);
				break;
			}
			default:
				break;
			}
		}
	}

	//this is messy
	for (int i = 0; i < ThingsToRender.size(); i++)
	{
		if (ThingsToRender[i] == TempSprite)
		{ 
			ThingsToRender.erase(ThingsToRender.begin() + i);
			delete TempSprite;
		}
	}
	
}
