#include "GameScreen.h"

GameScreen::GameScreen(Engine::D3D11Device* Device)
{
	mDevice = Device;
}

GameScreen::~GameScreen()
{
	//TODO DELETE EVERYTHING
}

void GameScreen::Render()
{
}

void GameScreen::UpdateTileMap(Vector2D Pos, int value)
{
	//awkward way of naming sprite but oh well
	std::string name;
	char buffer[50];
	int x = Pos.X, y = Pos.Y;
	sprintf(buffer, "Tile [ %d %d ]", x, y);
	name = buffer;
	//----
	//if value is 0 delete the tile
	if (value == 0)
	{
		for (int i = 0; i < ThingsToRender.size(); i++)
		{
			if (name == ThingsToRender[i]->GetName())
			{
				delete ThingsToRender[i];
				ThingsToRender.erase(ThingsToRender.begin() + i);
			}
		}
	}
	else
	{
		bool Match;
		for (int i = 0; i < ThingsToRender.size(); i++)
		{
			if (name == ThingsToRender[i]->GetName())
			{
				//change texture
				Match = true;
				break;
			}
			else
			{
				Match = false;
			}
		}
		if (!Match)
		{
			Sprite* mapItem = new Sprite(mDevice, name, std::string("Textures/stone.dds"), new vec2f(TILEWIDTH * Pos.Y, TILEHEIGHT * Pos.X));
			D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
			mapItem->AddRendererComponent(re);

			ThingsToRender.push_back(mapItem);
		}
	}

	


}

void GameScreen::Update(float deltaTime)
{
}
