#include "tileMapComp.h"
#include <Engine/Renderer/Device.h>
#include <Utils/AssetManager.h>

#include "Entities/GameObject.h"

namespace Engine
{
	TileMapComp::TileMapComp()
	{
	}

	TileMapComp::~TileMapComp()
	{
		mParent = nullptr;
		if (!mTexArray.empty())
			mTexArray.clear();
		
		if (!mRenderer.empty())
		{
			for (auto r : mRenderer)
			{
				delete r;
			}

			mRenderer.clear();
		}

		mTexture = nullptr;
		DefaultTexture = nullptr;
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
		if (IsACollison)
			return;
		if (mRenderer.empty())
			return;

		//int pos = 0;
		int ForX = 0;
		int ForY = 0;
		for (std::vector<int> firstPass : mTileMap)
		{
			for (int secondPass : firstPass)
			{
				if (secondPass < mTexArray.size())
				{
#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[secondPass]);
#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[0]);
#endif
				}
				else
				{
#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), DefaultTexture);
#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[0]);
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
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/0.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/1.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/2.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/3.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/4.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/5.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/6.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/7.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/8.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/9.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/10.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/11.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/12.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/13.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/14.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/15.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/16.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/17.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/18.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/19.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/20.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/21.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/22.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/23.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/24.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/25.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/26.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/27.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/28.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/29.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/30.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/31.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/32.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/33.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/34.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/35.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/36.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/37.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/38.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/39.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/40.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/41.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/42.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/43.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/44.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/45.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/46.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/47.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/48.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/49.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/50.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/51.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/52.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/53.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/54.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/55.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/56.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/57.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/58.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/59.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/60.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/61.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/62.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/63.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/64.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/65.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/66.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/67.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/68.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/69.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/70.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/71.png");
		mTexArray.push_back(mTexture);
		mTexture = AssetManager::GetInstance()->LoadTexture("Tile", "Assets/Textures/Numbers/72.png");
		mTexArray.push_back(mTexture);


		mType = COMPONENT_TILEMAP;
		LoadTileMap("Assets/TileMaps/XML_Test.xml");
		mRenderer.push_back(Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default")));
	}

	void TileMapComp::Start()
	{
	}

	void TileMapComp::InternalUpdate()
	{
	}

	void TileMapComp::InternalRender()
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
				if (secondPass < mTexArray.size())
				{
#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[secondPass]);
#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[0]);
#endif
				}
				else
				{
#if GRAPHICS_LIBRARY == 0
					dynamic_cast<D3D11Renderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), DefaultTexture);
#elif GRAPHICS_LIBRARY == 1
					dynamic_cast<OGLRenderer2D*>(mRenderer[0])->Draw(vec2f(ForY * TILEHEIGHT, ForX * TILEWIDTH) + mParent->GetComponent<TransformComp>()->GetPosition(), vec2f(0.0f), vec2f(1.0f), mTexArray[0]);
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
}
