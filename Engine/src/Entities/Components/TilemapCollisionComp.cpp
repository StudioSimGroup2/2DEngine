#include "TilemapCollisionComp.h"
#include "Entities/GameObject.h"

Engine::TilemapCollisionComp::TilemapCollisionComp()
{
}

Engine::TilemapCollisionComp::~TilemapCollisionComp()
{

}

void Engine::TilemapCollisionComp::CreateColBoxes()
{
	mTilemap = mParent->GetComponent<TileMapComp>()->GetTileMap();

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
				tempPos.x = (xPosVal * TILEWIDTH);
				tempPos.y = (yPosVal * TILEHEIGHT);

				tempColBox.SetPosition(tempPos);

				vec2f tempSize;
				tempSize.x = TILEWIDTH;
				tempSize.y = TILEHEIGHT;

				tempColBox.SetSize(tempSize);

				collisionBoxes.push_back(tempColBox);
			}

			if (item == 2)
			{
				Box2D tempColBox;

				vec2f tempPos;
				tempPos.x = (xPosVal * TILEWIDTH);
				tempPos.y = (yPosVal * TILEHEIGHT + (TILEHEIGHT / 2));

				tempColBox.SetPosition(tempPos);

				vec2f tempSize;
				tempSize.x = TILEWIDTH;
				tempSize.y = TILEHEIGHT / 2;

				tempColBox.SetSize(tempSize);

				collisionBoxes.push_back(tempColBox);
			}

			if (item == 3)
			{
				Box2D tempColBox;

				vec2f tempPos;
				tempPos.x = (xPosVal * TILEWIDTH);
				tempPos.y = (yPosVal * TILEHEIGHT + (3 * (TILEHEIGHT / 4)));

				tempColBox.SetPosition(tempPos);

				vec2f tempSize;
				tempSize.x = TILEWIDTH;
				tempSize.y = TILEHEIGHT / 4;

				tempColBox.SetSize(tempSize);

				collisionBoxes.push_back(tempColBox);
			}

			if (item == 4)
			{
				Box2D tempColBox;

				vec2f tempPos;
				tempPos.x = (xPosVal * TILEWIDTH);
				tempPos.y = (yPosVal * TILEHEIGHT);

				tempColBox.SetPosition(tempPos);

				vec2f tempSize;
				tempSize.x = TILEWIDTH / 2;
				tempSize.y = TILEHEIGHT;

				tempColBox.SetSize(tempSize);

				collisionBoxes.push_back(tempColBox);
			}

			if (item == 5)
			{
				Box2D tempColBox;

				vec2f tempPos;
				tempPos.x = (xPosVal * TILEWIDTH + (TILEWIDTH / 2));
				tempPos.y = (yPosVal * TILEHEIGHT);

				tempColBox.SetPosition(tempPos);

				vec2f tempSize;
				tempSize.x = TILEWIDTH / 2;
				tempSize.y = TILEHEIGHT;

				tempColBox.SetSize(tempSize);

				collisionBoxes.push_back(tempColBox);
			}

			xPosVal += 1;
		}

		xPosVal = 0;
		yPosVal += 1;
	}

	int a = 0;
}

void Engine::TilemapCollisionComp::Init()
{
	mType = COMPONENT_COLTILE;
	//Create Collision Boxes
	CreateColBoxes();
}

void Engine::TilemapCollisionComp::RefreshTileBoxes()
{
	collisionBoxes.clear();
	CreateColBoxes();
}

void Engine::TilemapCollisionComp::Update()
{

}

void Engine::TilemapCollisionComp::Render()
{

}

void Engine::TilemapCollisionComp::Start()
{
}

void Engine::TilemapCollisionComp::InternalUpdate()
{

}

void Engine::TilemapCollisionComp::InternalRender()
{
}
