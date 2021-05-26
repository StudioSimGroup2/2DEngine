#pragma once

#include "../Component.h"
#include "Common.h"
#include "../Box2D.h"
#include <vector>

namespace Engine
{
	class ENGINE_API TilemapCollisionComp : public Component
	{
	public:
		TilemapCollisionComp();
		TilemapCollisionComp(GameObject* parent);
		~TilemapCollisionComp();

		void CreateColBoxes();
		void Init();

		std::vector<Box2D> GetColBoxes() { return collisionBoxes; }

	private:
		TileMap mTilemap;
		std::vector<Box2D> collisionBoxes;

		//Inherited from Component
		virtual void Update() override;
		virtual void Render() override;
	};
}
