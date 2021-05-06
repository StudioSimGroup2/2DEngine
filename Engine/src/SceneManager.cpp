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

	void SceneManager::RenderScene()
	{
		mRenderToTex.Load();
		mCurrScene->Render();
		mRenderToTex.Unload();
	}

	void SceneManager::LoadScene()
	{
		mRenderToTex.CreateFrameBuffer(1260, 677);

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
