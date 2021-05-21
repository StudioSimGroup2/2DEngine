#include "TilemapCollisionComp.h"
#include "Entities/GameObject.h"

Engine::TilemapCollisionComp::TilemapCollisionComp() : Component()
{
	Init();
}

Engine::TilemapCollisionComp::TilemapCollisionComp(GameObject* parent) : Component(parent)
{
	Init();
}

Engine::TilemapCollisionComp::~TilemapCollisionComp()
{

}

void Engine::TilemapCollisionComp::CreateColBoxes()
{
	int xPosVal = 0;
	int yPosVal = 0;

	for (std::vector<int> firstPass : mTilemap)
	{
		for (int item : firstPass)
		{
			if (item == 1)
			{
				Box2D tempColBox;

				vec2f tempPos;
				tempPos.x = (xPosVal * 32) + 16;
				tempPos.y = (yPosVal * 32) + 16;

				tempColBox.SetPosition(tempPos);

				vec2f tempSize;
				tempSize.x = 32;
				tempSize.y = 32;

				tempColBox.SetSize(tempSize);

				collisionBoxes.push_back(tempColBox);
			}

			yPosVal += 1;
		}

		yPosVal = 0;
		xPosVal += 1;
	}

	int a = 0;
}

void Engine::TilemapCollisionComp::Init()
{
	mType = "Tilemap Collision";

	//Get Parent Tilemap
	mTilemap = mParent->GetComponent<TileMapComp>()->GetTileMap();
	//Create Collision Boxes
	CreateColBoxes();
}

void Engine::TilemapCollisionComp::Update()
{

}

void Engine::TilemapCollisionComp::Render()
{

}