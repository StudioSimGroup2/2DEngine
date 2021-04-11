#include "Scene.h"


// This class is useless, i was experimenting with trying to load stuff from the game project inside engine

namespace Engine
{
	Scene::Scene()
	{
		// Load info from file here

		GameObject* mPlayer = new GameObject();
		
		mPlayer->SetName("Parent");

		GameObject* firstChild = new GameObject(mPlayer);
		firstChild->SetName("I am a child");

		GameObject* secondChild = new GameObject(firstChild);
		secondChild->SetName("I am a grandchild");
		GameObject* mTest = new GameObject();

		GameObject* thirdChild = new GameObject(mTest);
		thirdChild->SetName("child");

		mTest->SetName("Object B");

		GameObject* childLess = new GameObject();
		childLess->SetName("nO Child");

		mSceneObjects.push_back(mPlayer);
		mSceneObjects.push_back(mTest);
		mSceneObjects.push_back(childLess);


		/// <summary>
		/// sprite class needs to be removed its useless now that we're actually setting up components
		/// </summary>
		SpriteComp* sprComp = mPlayer->AddComponent(new SpriteComp);
		Texture* stoneTex = AssetManager::GetInstance()->LoadTexture((char*)"Stone", (char*)"Assets/Textures/Stone.png");
		auto* instanceOfAClassThatReallyNeedsToBeCleanedUpXOX = new Sprite((char*)std::string("Tile").c_str(), new vec2f(32 * 12, 32 * 4), stoneTex);
		instanceOfAClassThatReallyNeedsToBeCleanedUpXOX->AddRendererComponent();
		sprComp->SetSprite(instanceOfAClassThatReallyNeedsToBeCleanedUpXOX);
	}

	Scene::~Scene()
	{
		if (!(mSceneObjects.empty()))
		{
			for (GameObject* go : mSceneObjects)
			{
				delete go;
				go = nullptr;
			}
		}
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