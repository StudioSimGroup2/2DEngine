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
		void CreateScene();

		void PlayScene();
		void UpdateScene();
		void RenderScene();

		void LoadScene(std::string path);
		void LoadObject(TiXmlElement* CurrentObject, GameObject* ParentObj);
		void SaveScene(std::string path);
		void SaveObject(TiXmlElement* components, GameObject* CurrentObj);
		void ClearScene();

		void EnableEditorMode() { mEditorMode = true; }
		void DisableEditorMode() { mEditorMode = false; }

		bool GetRunTime() { return mEditorMode; }

		GameObject* CreateObject();

		void DestroyObject(GameObject* go);

		std::vector<GameObject*>& GetSceneObjects() { return mSceneObjects; }
		GameObject* GetSceneObjectByName(std::string Name);


		bool IsSceneLoaded() { return mSceneLoaded; }
		bool HasUserNotSaved() { return mUnsavedChanges; }

		static void Shutdown();

		void* GetRenderToTexID() { return mRenderToTex.GetTexID(); }
	private:
		SceneManager() { }

		static SceneManager* mInstance;

		std::vector<GameObject*> mSceneObjects;

		bool mSceneLoaded = false;

		bool mUnsavedChanges = false;

		bool mEditorMode = true;
		FrameBuffer mRenderToTex;

		static int mCounter;
	};
}

