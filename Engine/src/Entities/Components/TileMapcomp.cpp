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
		for (int X = 0; X < Pos.x; X++)
		{
			if (Pos.x >= mTileMap.size())
			{
				mTileMap.push_back(std::vector<int>());
			}
			for (int Y = 0; Y < Pos.y; Y++)
			{
				if (Pos.y >= mTileMap[Pos.x].size())
				{
					mTileMap[X].push_back(10);
				}
				if (Pos.y >= mTileMap[X].size())
				{
					mTileMap[X].push_back(10);
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

		int pos = 0;
		int ForX = 0;
		int ForY = 0;
		for (std::vector<int> firstPass : mTileMap)
		{
			for (int secondPass : firstPass)
			{
				switch (secondPass)
				{
				case 0:
				{
					break;
				}
				case 1:
				{
	#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[pos])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexture);
	#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[pos])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexture);
	#endif
					pos++;
					break;
				}
				default:
					break;
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
				mTexture
			);
#elif GRAPHICS_LIBRARY == 1
			dynamic_cast<OGLRenderer2D*>(child)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
				mParent->GetComponent<TransformComp>()->GetRotation(),
				mParent->GetComponent<TransformComp>()->GetScale(),
				mTexture
			);
#endif
		}


	}
	void TileMapComp::Init()
	{
		
		mType = "TileMap";
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/TilesTest.png");
		LoadTileMap("Assets/TileMaps/XML_Test.xml");
		for (int X = 0; X < mTileMap.size(); X++)
		{
			for (int Y = 0; Y < mTileMap[0].size(); Y++)
			{
				switch (mTileMap[X][Y])
				{
				case 0:
				{
					break;
				}
				case 1:
				{
					mRenderer.push_back(Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default")));
					break;
				}
				default:
					break;
				}
			}
		}
	}
}
