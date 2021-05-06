#include "AssetManager.h"

#include "StringHelper.h"
#include "Utils\Logger.h"
#include <sstream>

#include <iostream>

namespace Engine
{
	AssetManager* AssetManager::mInstance = nullptr;

	void AssetManager::LoadShader(const std::string& name, const std::string& path)
	{
#if GRAPHICS_LIBRARY == 0
		mInstance->mShaders.push_back(new D3D11Shader(D3D11Device::GetInstance(), name, path));
#elif GRAPHICS_LIBRARY == 1
		mInstance->mShaders.push_back(new OGLShader(name, path));
#endif
	}

//	void AssetManager::ChangeTexture(Texture* tex, const std::string& path)
//	{
//		bool err = true;
//		for (auto& mSupportedTexExtension : mInstance->mSupportedTexExtensions)
//		{
//			if (StringHelper::GetFileExtension(path) == mSupportedTexExtension)
//			{
//				err = false;
//			}
//		}
//
//		if (err)
//		{
//			std::ostringstream output;
//			output << "The File extension : " << StringHelper::GetFileExtension(path) << " is not supported!\n";
//
//			Logger::LogError(output.str().c_str());
//		}
//
//#if GRAPHICS_LIBRARY == 0
//		tex->SetPath(path);
//		dynamic_cast<D3D11Texture*>(tex)->CreateTextureFromFile(D3D11Device::GetInstance());
//#elif GRAPHICS_LIBRARY == 1
//		tex->SetPath(path);
//#endif
//	}

	Texture* AssetManager::LoadTexture(const std::string& name, const std::string& path)
	{
		bool err = true;
		for (auto & mSupportedTexExtension : mInstance->mSupportedTexExtensions)
		{
			if (StringHelper::GetFileExtension(path) == mSupportedTexExtension)
			{
				err = false;
			}
		}

		if (err)
		{
			std::ostringstream output;
			output << "The File extension : " << StringHelper::GetFileExtension(path) << " is not supported!\n";

			Logger::LogError(output.str().c_str());
			return nullptr;
		}

#if GRAPHICS_LIBRARY == 0
		mInstance->mTextures.push_back(new D3D11Texture(D3D11Device::GetInstance(), name, path));
#elif GRAPHICS_LIBRARY == 1
		mInstance->mTextures.push_back(new OGLTexture(name, path));
#endif
		return mInstance->mTextures.back();
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
			[&name](Texture* s) {return s->GetName() == name; });

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

	void AssetManager::ClearAll()
	{
		for (Shader* s : mInstance->mShaders)
		{
			delete s;
			s = nullptr;
		}
			

		for (Texture* t : mInstance->mTextures)
		{
			delete t;
			t = nullptr;
		}
	}

	void AssetManager::Shutdown()
	{
		if (mInstance == nullptr)
			return;
		
		mInstance->ClearAll();

		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
}