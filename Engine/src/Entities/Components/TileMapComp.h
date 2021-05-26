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
		~TileMapComp() override;

		virtual void Init() override;

		void SetTileMap(TileMap InMap) { mTileMap = InMap; };
		void LoadTileMap(const std::string& FilePath) { mTileMap = LevelMap::LoadLevelMap(FilePath); };
		void SaveTileMap(const std::string& FilePath, vec2i Size) { LevelMap::SaveTileMap(mTileMap, FilePath); };
		TileMap GetTileMap() { return mTileMap; };
		std::vector<Texture*> GetTextures() { return mTexArray; };
		void ChangeTile(int ID, vec2i Pos);

		void ChangeTexture();

		void Update();
		void Render();

		std::string getpath() { return mFilePath; };
		void Setpath(std::string path) { mFilePath = path; };
	private:
		TileMap mTileMap;

		Texture* mTexture = nullptr;
		Texture* DefaultTexture = nullptr;
		std::vector<Texture*> mTexArray;
		std::vector<Renderer2D*> mRenderer;
		int TextureWidth = 1, TextureHeight = 1;

		std::string mFilePath;

		// Inherited via Component
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;
	};
}