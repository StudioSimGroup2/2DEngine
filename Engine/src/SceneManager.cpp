#include "SceneManager.h"
#include "Scripting\ScriptingEngine.h"

namespace Engine
{
	SceneManager* SceneManager::mInstance = nullptr;
	
	SceneManager* SceneManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new SceneManager();

		return mInstance;
	}

	void SceneManager::LoadScene()
	{
		ScriptingEngine::GetInstance()->Init();
		
		mRenderToTex.CreateFrameBuffer(1260, 677);
		mSceneLoaded = true;
	}

	void SceneManager::PlayScene()
	{
		mEditorMode = false;
		for (GameObject* go : mSceneObjects)
		{
			go->Start();
		}
	}

	void SceneManager::UpdateScene()
	{
		if (mEditorMode)
		{
			for (GameObject* go : mSceneObjects)
			{
				go->InternalUpdate();
			}
		}
		else
		{
			for (GameObject* go : mSceneObjects)
			{
				go->Update();
			}
		}
	}

	void SceneManager::RenderScene()
	{
		mRenderToTex.Load();

        for (GameObject* go : mSceneObjects)
		{
			go->Render();
		}

        mRenderToTex.Unload();
	}

	void SceneManager::SaveScene()
	{
	}

	GameObject* SceneManager::CreateObject()
	{
		GameObject* go = new GameObject();
		mSceneObjects.push_back(go);
		go->SetName("Unnamed Object " + std::to_string(mSceneObjects.size()));

		return go;
	}

	GameObject* SceneManager::DestroyObject()
	{
		std::cout << "Called Destroy Object" << std::endl;

		return nullptr;
	}

	void SceneManager::Shutdown()
	{
		if (mInstance == nullptr)
			return;

		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
}
