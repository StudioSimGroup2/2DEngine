#pragma once
#include <Entities/GameObject.h>
#include <vector>

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

		void PlayScene() { }
		void UpdateScene();
		void RenderScene();

		void SaveScene();

		GameObject* CreateObject();
		//void CreateObject(GameObject* parent);

		GameObject* DestroyObject();

		std::vector<GameObject*> GetSceneObjects() { return mSceneObjects; }

		bool IsSceneLoaded() { return (mSceneLoaded); }

		static void Shutdown();
	private:
		SceneManager() { }

		static SceneManager* mInstance;

		std::vector<GameObject*> mSceneObjects;

		bool mSceneLoaded = false;
	};
}

