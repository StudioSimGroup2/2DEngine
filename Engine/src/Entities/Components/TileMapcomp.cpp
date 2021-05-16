#include "tileMapComp.h"
#include <Engine/Renderer/Device.h>
#include <Utils/AssetManager.h>

#include "Entities/GameObject.h"

namespace Engine
{
	TileMapComp::TileMapComp()
	{
		Init();
	}
	TileMapComp::TileMapComp(GameObject* parent)
	{
	}
	TileMapComp::~TileMapComp()
	{
	}

	void TileMapComp::ChangeTile(int ID, vec2i Pos)
	{
		if (Pos.x < 0 || Pos.y < 0)
		{
			return;
		}

		//Make current tilemap bigger if the mouse postion lies outside the tilemap boundries
		for (int X = 0; X <= Pos.x; X++)
		{
			if (Pos.x >= mTileMap.size())
			{
				mTileMap.push_back(std::vector<int>());
			}
			for (int Y = 0; Y <= Pos.y; Y++)
			{
				if (Pos.y >= mTileMap[X].size())
				{
					mTileMap[X].push_back(0);
				}
			}
		}
		if (Pos.x >= mTileMap.size())
		{
			int i = 0;
		}
		for (int X = 0; X < Pos.x; X++)
		{
			if (Pos.y >= mTileMap[X].size())
			{
				int i = 0;
			}
		}
		//if tile is that currently selected. Do nothing
		//else change tile to that selected
		if (mTileMap[Pos.x][Pos.y] == ID)
		{
			return;
		}
		else
		{
			mTileMap[Pos.x][Pos.y] = ID;				
		}		
		//update the renderer
	}

	void TileMapComp::ChangeTexture()
	{
	}

	void TileMapComp::Update()
	{

	}

	void TileMapComp::Render()
	{
		if (mRenderer.empty())
			return;

		//int pos = 0;
		int ForX = 0;
		int ForY = 0;
		for (std::vector<int> firstPass : mTileMap)
		{
			for (int secondPass : firstPass)
			{
				//switch (secondPass)
				//{
				//case 0:
				//{
				//	break;
				//}
				//case 1:
				//{

				//	pos++;
				//	break;
				//}
				//default:
				//	break;
				//}
				if (secondPass < mTexArray.size())
				{
#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[secondPass]);
#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[pos])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[0]);
#endif
				}
				else
				{
#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), DefaultTexture);
#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[pos])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[0]);
#endif
				}
				
				ForY++;
			}
			ForY = 0;
			ForX++;
		}

		for (Renderer2D* child : mRenderer)
		{
#if GRAPHICS_LIBRARY == 0
			dynamic_cast<D3D11Renderer2D*>(child)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
				mParent->GetComponent<TransformComp>()->GetRotation(),
				mParent->GetComponent<TransformComp>()->GetScale(),
				mTexArray[0]
			);
#elif GRAPHICS_LIBRARY == 1
			dynamic_cast<OGLRenderer2D*>(child)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
				mParent->GetComponent<TransformComp>()->GetRotation(),
				mParent->GetComponent<TransformComp>()->GetScale(),
				mTexArray[0]
			);
#endif
		}


	}
	void TileMapComp::Init()
	{
		
		//DefaultTexture for if texture array is out of range
		DefaultTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Mario.png");

		//defult textures for map painting 
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/zero.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/one.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/two.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/three.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/four.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/five.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/six.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/seven.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/eight.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/nine.png");
		mTexArray.push_back(mTexture);
		mType = COMPONENT_TILEMAP;
		LoadTileMap("Assets/TileMaps/XML_Test.xml");
		mRenderer.push_back(Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default")));
		/*for (int X = 0; X < mTileMap.size(); X++)
		{
			for (int Y = 0; Y < mTileMap[0].size(); Y++)
			{
				switch (mTileMap[X][Y])
				{
				case 1:
				{
					
					break;
				}
				default:
					break;
				}
			}
		}*/
	}

	void TileMapComp::Start()
	{
	}

	void TileMapComp::InternalUpdate()
	{
	}

	void TileMapComp::InternalRender()
	{
	}
}
