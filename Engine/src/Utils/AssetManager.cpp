#include "AssetManager.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend/D3D11/D3D11Shader.h"
#include "Backend/D3D11/D3D11Device.h"
#include "Backend/D3D11/D3D11Texture.h"
#elif GRAPHICS_LIBRARY == 1
#include "Backend/OGL/OGLShader.h"
#include "Backend/OGL/OGLTexture.h"
#endif

namespace Engine
{
	AssetManager* AssetManager::mInstance = nullptr;
	

	void AssetManager::LoadShader(Device* device, const std::string& name, const std::string& path)
	{
#if GRAPHICS_LIBRARY == 0
		mInstance->mShaders.push_back(new D3D11Shader(static_cast<D3D11Device*>(device), name, path));
#elif GRAPHICS_LIBRARY == 1
		mInstance->mShaders.push_back(new OGLShader(name, path));
#endif
	}

	Texture* AssetManager::LoadTexture(Device* device, const std::string& name, const std::string& path)
	{
#if GRAPHICS_LIBRARY == 0
		mInstance->mTextures.push_back(new D3D11Texture(static_cast<D3D11Device*>(device), name, path));
#elif GRAPHICS_LIBRARY == 1
		mInstance->mTextures.push_back(new OGLTexture(name, path));
#endif
		return mInstance->mTextures.back();
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
		auto index = std::find_if(mInstance->mShaders.begin(), mInstance->mShaders.end(),
			[&name](const Shader* s) {return s->GetName() == name; });

		return mInstance->mShaders.at(std::distance(mInstance->mShaders.begin(), index));
	}

	Texture* AssetManager::GetTextureByName(const std::string& name)
	{
		auto index = std::find_if(mInstance->mTextures.begin(), mInstance->mTextures.end(),
			[&name](const Texture* s) {return s->GetName() == name; });

		return mInstance->mTextures.at(std::distance(mInstance->mTextures.begin(), index));
	}

	Sound* AssetManager::GetSoundByName(const std::string& name)
	{
		/*auto match = std::find_if(mInstance->mShaders.begin(), mInstance->mShaders.begin(), [](const Sound* s) { return s->GetNa(); });
		return mInstance->mShaders.at(std::distance(mInstance->mShaders.begin(), match));*/
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

	void AssetManager::Shutdown()
	{
		delete mInstance;
	}
}