#include "AssetManager.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend/D3D11/D3D11Shader.h"
#include "Backend/D3D11/D3D11Device.h"
#elif GRAPHICS_LIBRARY == 1
#include "Backend/OGL/OGLShader.h"
#endif

namespace Engine
{
	AssetManager* AssetManager::mInstance = nullptr;

	void AssetManager::LoadShader(const std::string& name, const std::string& path)
	{
#if GRAPHICS_LIBRARY == 0
		mInstance->mShaders.push_back(new D3D11Shader(static_cast<D3D11Device*>(mInstance->mDevice), path, name));
#elif GRAPHICS_LIBRARY == 1
#endif
	}

	void AssetManager::LoadTexture(const std::string& name, const std::string& path)
	{
#if GRAPHICS_LIBRARY == 0
		//mInstance->mTextures.push_back
#elif GRAPHICS_LIBRARY == 1
#endif
	}

	void AssetManager::LoadSound(const std::string& name, const std::string& path)
	{
	}

	AssetManager* AssetManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new AssetManager();
		
		return mInstance;
	}

	Shader* AssetManager::GetShaderByName(const std::string& name)
	{
		return nullptr;
	}

	Texture* AssetManager::GetTextureByName(const std::string& name)
	{
		return nullptr;
	}

	Sound* AssetManager::GetSoundByName(const std::string& name)
	{
		return nullptr;
	}

	void AssetManager::RemoveShader(const std::string& name)
	{
	}

	void AssetManager::RemoveTexture(const std::string& name)
	{
	}

	void Engine::AssetManager::RemoveSound(const std::string& name)
	{
	}

	void AssetManager::ClearAll()
	{
	}
}