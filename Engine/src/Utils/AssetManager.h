#pragma once

#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "Sound.h"
#include <Engine/Renderer/Device.h>

namespace Engine
{
	class AssetManager
	{
	public:
		static void LoadShader(const std::string& name, const std::string& path);
		static void LoadTexture(const std::string& name, const std::string& path);
		static void LoadSound(const std::string& name, const std::string& path);

		static AssetManager* GetInstance();

		static Shader* GetShaderByName(const std::string& name);
		static Texture* GetTextureByName(const std::string& name);
		static Sound* GetSoundByName(const std::string& name);

		static void RemoveShader(const std::string& name);
		static void RemoveTexture(const std::string& name);
		static void RemoveSound(const std::string& name);

		void SetDevice(Device* dev) { mDevice = dev; }

		static void ClearAll();
	private:
		AssetManager() { };

		Device* mDevice;

		std::vector<Shader*> mShaders;
		std::vector<Texture*> mTextures;
		std::vector<Sound*> mSounds;

		static AssetManager* mInstance;
	};
}

