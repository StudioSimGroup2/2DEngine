#include "Scene.h"


// This class is useless, i was experimenting with trying to load stuff from the game project inside engine

namespace Engine
{
	Scene::Scene()
	{
		// Load info from file here

		// MOVED TO SCENEMANAGER.CPP

		/*AudioManager::GetInstance()->LoadSound("z", "zip.wav");
		AudioManager::GetInstance()->PlaySoundFile("z", 0.2, false);*/
	}

	Scene::~Scene()
	{
		for (GameObject* go : mSceneObjects)
		{
			delete go;
			go = nullptr;
		}

		mSceneObjects.shrink_to_fit();
	}

	void Scene::Init()
	{
		for (GameObject* go : mSceneObjects)
		{
			go->Start();
		}
	}

	void Scene::Start()
	{
	}

	void Scene::Update()
	{
		for (GameObject* go : mSceneObjects)
		{
			go->Update();

			if (go->GetComponent<Engine::PhysicsComp>() != NULL)
			{
				for (GameObject* compObj : mSceneObjects)
				{
					if (go == compObj)
					{
						continue;
					}

					if (Collision::CheckCollision(go, compObj))
					{
						go->GetComponent<Engine::PhysicsComp>()->SetGrounded(true);
						break;
					}
					else
					{
						go->GetComponent<Engine::PhysicsComp>()->SetGrounded(false);
					}
				}
			}
		}
	}

	void Scene::FixedUpdate()
	{
		/*for (GameObject* go : mSceneObjects)
		{

		}*/
	}

	void Scene::LateUpdate()
	{
		/*for (GameObject* go : mSceneObjects)
		{

		}*/
	}

	void Scene::Render()
	{
		for (GameObject* go : mSceneObjects)
		{
			go->Render();
		}
	}

}