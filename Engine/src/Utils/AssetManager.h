#pragma once

#include <vector>
#include <string>

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
		void LoadShader(const char* name, const char* path);
		//static void LoadTexture(Device* device, const std::string& name, const std::string& path);
		Texture* LoadTexture(char* name, char* path);

		static AssetManager* GetInstance();

		Shader* GetShaderByName(const char* name);
		Texture* GetTextureByName(char* name);
		Sound* GetSoundByName(const std::string& name);

		void RemoveShader(const std::string& name);
		void RemoveTexture(const std::string& name);

		void ClearAll();

		void Shutdown();
	private:
		AssetManager() { }

		std::string mSupportedTexExtensions[1] = { "png"};

		std::vector<Shader*> mShaders;
		std::vector<Texture*> mTextures;
		//std::vector<Sound*> mSounds;

		static AssetManager* mInstance;
	};
}