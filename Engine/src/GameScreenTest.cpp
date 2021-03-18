#include "GameScreenTest.h"
#include <Sprite.h>
#include <Backend/D3D11/D3D11Renderer2D.h>


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
	//if (GetAsyncKeyState(0x27)) //Right arrow
	//{
	//	TestCharacter->setMovingRight(true);
	//}
	//else
	//{
	//	TestCharacter->setMovingRight(false);
	//}

	//if (GetAsyncKeyState(0x25)) //Left arrow
	//{
	//	TestCharacter->setMovingLeft(true);
	//}
	//else
	//{
	//	TestCharacter->setMovingLeft(false);
	//}

	//TestCharacter->Update(deltaTime);
}

void GameScreenTest::Render()
{
	for (auto Thing : ThingsToRender)
	{
		Thing->Draw();
	}

	/*TestCharacter->Render(mContext);*/
}

void GameScreenTest::Initalise()
{
	
	
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
				Sprite* mapItem = new Sprite(mDevice, std::string("Tile ") + std::string(X + "" + Y) + std::string("]"), 
					std::string("Textures/stone.dds"), vec2f(TILEWIDTH * Y, TILEHEIGHT * X));
				D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
				mapItem->AddRendererComponent(re);

				ThingsToRender.push_back(mapItem);
				break;
			}
			default:
				break;
			}
		}
	}

	Vector2D* Position = new Vector2D(32, 32);
	//TestCharacter = new Character(mDevice, L"Textures/Mario.dds", Position);
}
