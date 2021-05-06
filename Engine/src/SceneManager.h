#pragma once

#include "Scene.h"
#include "Engine\Renderer\FrameBuffer.h"

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
		void RenderScene();

		void SaveScene();

		std::vector<GameObject*> GetSceneObjects() { return mCurrScene->GetSceneObjects(); }

		bool IsSceneLoaded() { return (mSceneLoaded); }

		static void Shutdown();

		void* GetRenderToTexID() { return mRenderToTex.GetTexID(); }
	private:
		SceneManager() { }

		static SceneManager* mInstance;

		bool mSceneLoaded = false;

		Scene* mCurrScene;

		FrameBuffer mRenderToTex;
	};
}

