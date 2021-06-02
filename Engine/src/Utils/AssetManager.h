#pragma once

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

#include <vector>
#include <string>
#include <algorithm>

#include <Engine/Core.h>

#include "Shader.h"
#include "Texture.h"
#include "Sound.h"
#include <Engine/Renderer/Device.h>

namespace Engine
{
	class ENGINE_API AssetManager
	{
	public:
		Shader* LoadShader(const std::string& name, const std::string& path);
		void ChangeTexture(Texture* tex, const std::string& path);
		//static void LoadTexture(Device* device, const std::string& name, const std::string& path);
		Texture* LoadTexture(const std::string& name, const std::string& path);
		Texture* LoadSpriteSheet(const std::string& name, const std::string& path, int numberOfSprites);

		static AssetManager* GetInstance();

		Shader* GetShaderByName(const std::string& name);
		Texture* GetTextureByName(const std::string& name);
		std::vector<Texture*>* GetAllTextures() { return &mTextures; }
		// Sound* GetSoundByName(const std::string& name);

		void RemoveShader(const std::string& name);
		void RemoveTexture(const std::string& name);

		void ClearAll();

		static void Shutdown();
	private:
		AssetManager() { }

		std::string mSupportedTexExtensions[1] = { "png"};

		std::vector<Shader*> mShaders;
		std::vector<Texture*> mTextures;
		//std::vector<Sound*> mSounds;

		static AssetManager* mInstance;
	};
}