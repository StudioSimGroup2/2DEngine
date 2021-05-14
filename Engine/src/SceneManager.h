#pragma once
#include <Entities/GameObject.h>
#include <vector>

#include "Scene.h"
#include "Engine\Renderer\FrameBuffer.h"

//TODO: Load Scene

namespace Engine
{
	class ENGINE_API SceneManager
	{
	public:
		static SceneManager* GetInstance();

		// TODO: Read from file
		void LoadScene();

		void PlayScene();
		void UpdateScene();
		void RenderScene();

		void SaveScene();

		void EnableEditorMode() { mEditorMode = true; }
		void DisableEditorMode() { mEditorMode = false; }

		GameObject* CreateObject();
		//void CreateObject(GameObject* parent);

		GameObject* DestroyObject();

		std::vector<GameObject*>& GetSceneObjects() { return mSceneObjects; }

		bool IsSceneLoaded() { return (mSceneLoaded); }

		static void Shutdown();

		void* GetRenderToTexID() { return mRenderToTex.GetTexID(); }
	private:
		SceneManager() { }

		static SceneManager* mInstance;

		std::vector<GameObject*> mSceneObjects;

		bool mSceneLoaded = false;

		bool mEditorMode = true;
		FrameBuffer mRenderToTex;
	};
}

