#pragma once

#include "../Component.h"
#include "Common.h"
#include "Box2D.h"
#include <vector>
#include "Engine/Renderer/Renderer2D.h"

namespace Engine
{
	class ENGINE_API TilemapCollisionComp : public Component
	{
	public:
		TilemapCollisionComp();
		~TilemapCollisionComp();

		void CreateColBoxes();
		virtual void Init() override;

		std::vector<Box2D>& GetColBoxes() { return collisionBoxes; }

		float GetBRange() { return boundingRange; }
		void SetBRange(float newRange) { boundingRange = newRange; }

		bool GetTrigger() { return isTrigger; }
		void SetTrigger(bool newTrigger) { isTrigger = newTrigger; }

		bool GetColToggle() { return isCollidable; }
		void SetColToggle(bool newColToggle) { isCollidable = newColToggle; }

		void RefreshTileBoxes();

		// Inherited via Component
		virtual void Update() override;
		virtual void Render() override;

		// Inherited via Component
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

	private:
		bool isCollidable = true;
		bool isTrigger = false;
		float boundingRange = 300;
		TileMap mTilemap;
		std::vector<Box2D> collisionBoxes;
		Renderer2D* mRenderer;
		Texture* mTexture;
	};
}
