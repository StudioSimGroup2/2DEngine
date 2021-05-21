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

	void SceneManager::CreateScene()
	{
		ScriptingEngine::GetInstance()->Init();
		
		mRenderToTex.CreateFrameBuffer(1260, 677);
		mSceneLoaded = true;
	}

	void SceneManager::PlayScene()
	{
		mEditorMode = false;
		for (GameObject* go : mSceneObjects)
		{
			go->Start();
		}
	}

	void SceneManager::UpdateScene()
	{
		if (mEditorMode)
		{
			for (GameObject* go : mSceneObjects)
			{
				go->InternalUpdate();
			}
		}
		else
		{
			for (GameObject* go : mSceneObjects)
			{
				go->Update();
			}
		}
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

	void SceneManager::LoadScene(std::string path)
	{
		//Clear the scene befoer loading anything in
		ClearScene();

		TiXmlDocument doc;
		if (!doc.LoadFile(path.c_str()))
		{
			std::cerr << doc.ErrorDesc() << std::endl;
		}

		//Now get the root element.
		TiXmlElement* root = doc.FirstChildElement();
		if (!root)
		{
			std::cerr << "Failed to load file: No root element." << std::endl;
			doc.Clear();
		}
		else
		{
			root = root->FirstChildElement();
			//Loop through all GameObjects
			for (TiXmlElement* CurrentObject = root->FirstChildElement(); CurrentObject != NULL; CurrentObject = CurrentObject->NextSiblingElement())
			{
				GameObject* NewObject = CreateObject();
				
				NewObject->SetName(CurrentObject->Attribute("name"));
				TiXmlElement* comps = CurrentObject->FirstChildElement();
				for (TiXmlElement* CurrentComp = comps->FirstChildElement(); CurrentComp != NULL; CurrentComp = CurrentComp->NextSiblingElement())
				{
					//transform / sprite / physics / script /  tilemap
					std::string CompType = CurrentComp->Value();
					if (CompType == "transform")
					{
						//Position / Rotation / scale

						//get pos
						vec2f Pos;
						Pos.x = atof(CurrentComp->Attribute("x"));
						Pos.y = atof(CurrentComp->Attribute("y"));
						//set Pos to newobject
						TransformComp* Transform = NewObject->GetComponent<TransformComp>();
						Transform->SetPosition(Pos);

						//TODO add
						//rotation
						//scale						
					}
					else if (CompType == "sprite")
					{
						//Texture / colour / flip X / flip Y
						SpriteComp* NewSprite = new SpriteComp();
						//Texture
						NewSprite->SetTexture(AssetManager::GetInstance()->LoadTexture(NewObject->GetName(),CurrentComp->Attribute("path")));
						//Colour

						//flipX
						std::string FX = CurrentComp->Attribute("FlipX");
						if (FX == "1")
						{
							NewSprite->ToggleFlipX(true);
						}
						//flipY
						std::string FY = CurrentComp->Attribute("FlipY");
						if (FY == "1")
						{
							NewSprite->ToggleFlipY(true);
						}

						NewObject->AddComponent<SpriteComp>(NewSprite);
					}
					else if (CompType == "physics")
					{
						int i = 0;
					}
					else if (CompType == "script")
					{
						int i = 0;
					}					
					else if (CompType == "tilemap")
					{
						int i = 0;
					}
				}
				//Create object in hierarchy

			}
		}
	}

	void SceneManager::SaveScene()
	{
	}
	void SceneManager::ClearScene()
	{
		mSceneObjects.clear();
	}

	GameObject* SceneManager::CreateObject()
	{
		GameObject* go = new GameObject();
		mSceneObjects.push_back(go);
		go->SetName("Unnamed Object " + std::to_string(mSceneObjects.size()));

		return go;
	}

	GameObject* SceneManager::CreateObject(GameObject*)
	{
		return nullptr;
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
