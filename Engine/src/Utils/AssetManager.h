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
		static void LoadShader(char* name, char* path);
		//static void LoadTexture(Device* device, const std::string& name, const std::string& path);
		static Texture* LoadTexture(char* name, char* path);


		static AssetManager* GetInstance();

		static Shader* GetShaderByName(char* name);
		static Texture* GetTextureByName(char* name);
		static Sound* GetSoundByName(const std::string& name);

		static void RemoveShader(const std::string& name);
		static void RemoveTexture(const std::string& name);


		static void ClearAll();

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