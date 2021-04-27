//#include "Scene.h"
//#include <SceneManager.h>
//
//// This class is useless, i was experimenting with trying to load stuff from the game project inside engine
//
//namespace Engine
//{
//	Scene::Scene()
//	{
//		// Load info from file here
//
//		AudioManager::GetInstance()->LoadSound("z", "zip.wav");
//		AudioManager::GetInstance()->PlaySoundFile("z", 0.2, false);
//	}
//
//	void Scene::Init()
//	{
//		GameObject* mPlayer = SceneManager::GetInstance()->CreateObject();
//		std::cout << mPlayer << std::endl;
//
//		mPlayer->SetName("Parent");
//
//		SpriteComp* spr = mPlayer->AddComponent(new SpriteComp);
//		//mPlayer->GetComponent<TransformComp>()->SetPosition(200.0f, 200.0f);
//		spr->SetTexture(AssetManager::GetInstance()->LoadTexture((char*)"Stone", (char*)"Assets/Textures/Stone.png"));
//		std::cout << mPlayer << std::endl;
//	}
//
//	Scene::~Scene()
//	{
//		for (GameObject* go : mSceneObjects)
//		{
//			delete go;
//			go = nullptr;
//		}
//
//		mSceneObjects.shrink_to_fit();
//	}
//
//	//void Scene::Init()
//	//{
//	//	/*for (GameObject* go : mSceneObjects)
//	//	{
//	//		go->Start();
//	//	}*/
//	//}
//
//	void Scene::Start()
//	{
//	}
//
//	void Scene::Update()
//	{
//		for (GameObject* go : mSceneObjects)
//		{
//			go->Update();
//		}
//	}
//
//	void Scene::FixedUpdate()
//	{
//		/*for (GameObject* go : mSceneObjects)
//		{
//
//		}*/
//	}
//
//	void Scene::LateUpdate()
//	{
//		/*for (GameObject* go : mSceneObjects)
//		{
//
//		}*/
//	}
//
//	void Scene::Render()
//	{
//		for (GameObject* go : mSceneObjects)
//		{
//			go->Render();
//		}
//	}
//
//}