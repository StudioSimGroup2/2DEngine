#pragma once

#include "../Component.h"
#include "../../Utils/LevelMap.h"
#include "Utils/Texture.h"
#include <Engine/Renderer/Renderer2D.h>
#include <vector>

namespace Engine
{
	class ENGINE_API TileMapComp : public Component
	{
	public:
		TileMapComp();
		TileMapComp(GameObject* parent);
		~TileMapComp() override;

		void SetTileMap(TileMap InMap) {mTileMap = InMap; };
		void LoadTileMap(char* FilePath) { mTileMap = LevelMap::LoadLevelMap(FilePath); };
		TileMap GetTileMap() { return mTileMap;  };


		void Update();
		void Render();
	private:
		void Init();
		TileMap mTileMap;

		Texture* mTexture = nullptr;
		std::vector<Renderer2D*> mRenderer;
	};
}