#include "SceneManager.h"

namespace Engine
{
	SceneManager* SceneManager::mInstance = nullptr;
	
	SceneManager* SceneManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new SceneManager();

		return mInstance;
	}

	void SceneManager::Init()
	{
		
	}

	void SceneManager::LoadScene()
	{
		mCurrScene = new Scene();
		mSceneLoaded = true;
	}

	void SceneManager::SaveScene()
	{
	}

	void SceneManager::Shutdown()
	{
		if (mInstance == nullptr)
			return;

		if (mInstance->mCurrScene)
		{
			delete mInstance->mCurrScene;
			mInstance->mCurrScene = nullptr;
		}

		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
}
