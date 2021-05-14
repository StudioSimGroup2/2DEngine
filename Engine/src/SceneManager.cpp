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
		GameObject* mPlayer = new GameObject();

		mPlayer->SetName("Parent");

		SpriteComp* spr = mPlayer->AddComponent(new SpriteComp);
		mPlayer->GetComponent<TransformComp>()->SetPosition(vec2f(200.0f, 200.0f));
		spr->SetTexture(AssetManager::GetInstance()->LoadTexture((char*)"Stone", (char*)"Assets/Textures/Stone.png"));
		mPlayer->AddComponent(new PhysicsComp());

		mSceneObjects.push_back(mPlayer);

		GameObject* mLevelMap = new GameObject();
		TileMapComp* TM = mLevelMap->AddComponent(new TileMapComp);
		TM->LoadTileMap("Assets/TileMaps/XML_Test.xml");
		mLevelMap->SetName("tileMapTest");

		mSceneObjects.push_back(mLevelMap);

		mRenderToTex.CreateFrameBuffer(1260, 677);

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
