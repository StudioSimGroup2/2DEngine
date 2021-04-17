#pragma once

#include "Scene.h"

//TODO: Load Scene

namespace Engine
{
	class ENGINE_API SceneManager
	{
	public:
		static SceneManager* GetInstance();
		
		void Init();

		// TODO: Read from file
		void LoadScene();

		void PlayScene() { mCurrScene->Init(); }
		void UpdateScene() { mCurrScene->Update(); }
		void RenderScene() { mCurrScene->Render(); }

		void SaveScene();

		GameObject* CreateObject();
		//void CreateObject(GameObject* parent);

		GameObject* DestroyObject();

		std::vector<GameObject*> GetSceneObjects() { return mCurrScene->GetSceneObjects(); }

		bool IsSceneLoaded() { return (mSceneLoaded); }

		static void Shutdown();
	private:
		SceneManager() { }

		static SceneManager* mInstance;

		bool mSceneLoaded = false;

		Scene* mCurrScene;
	};
}

