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

	void SceneManager::Init()
	{
		
	}

	void SceneManager::LoadScene()
	{
		mSceneLoaded = true;
	}

	void SceneManager::UpdateScene()
	{
		for (GameObject* go : mSceneObjects)
		{
			go->Update();
		}

		ScriptingEngine::GetInstance()->Update();
	}

	void SceneManager::RenderScene()
	{
		for (GameObject* go : mSceneObjects)
		{
			go->Render();
		}
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
