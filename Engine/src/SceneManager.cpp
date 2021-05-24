#include "SceneManager.h"
#include "Scripting\ScriptingEngine.h"
#include "CameraManager.h"

namespace Engine
{
	SceneManager* SceneManager::mInstance = nullptr;
	int SceneManager::mCounter = 0;
	
	SceneManager* SceneManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new SceneManager();

		return mInstance;
	}

	void SceneManager::CreateScene()
	{
		auto camera = CameraManager::Get()->Add(vec2f(0.0f, 0.0f), true);		// Camera manager deletes its cameras, no mem leak :)         
		camera->SetName("Main Camera");
		camera->SetPrimary(true);
		camera->SetEditorCamera(true);
		
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
						Pos.x = atof(CurrentComp->Attribute("PosX"));
						Pos.y = atof(CurrentComp->Attribute("PosY"));
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
						std::string path = CurrentComp->Attribute("path");
						if (path != "")
						{
							NewSprite->SetTexture(AssetManager::GetInstance()->LoadTexture(NewObject->GetName(), path));
							NewSprite->Setpath(path);
						}
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
						//mass / gravity / friction
						PhysicsComp* NewPhysics = new PhysicsComp;
						NewObject->AddComponent<PhysicsComp>(NewPhysics);
					}
					else if (CompType == "script")
					{
						//Path
						ScriptComp* NewScript = new ScriptComp;
						NewObject->AddComponent<ScriptComp>(NewScript);
						std::string path = CurrentComp->Attribute("path");
						if (path != "")
						{
							NewScript->AddScript(path);
							NewScript->Setpath(path);

						}
					}					
					else if (CompType == "tilemap")
					{
						//path
						TileMapComp* NewtileMap = new TileMapComp;
						NewObject->AddComponent<TileMapComp>(NewtileMap);
						std::string path = CurrentComp->Attribute("path");
						if (path != "")
						{
							NewtileMap->LoadTileMap(path);
							NewtileMap->Setpath(path);
						}
					}
				}
			}
			// TODO:
			// Lots of pointers left here should clean them up when done with them
		}
	}

	void SceneManager::SaveScene(std::string path)
	{
		//Test for saving to XML file
		TiXmlDocument Doc;
		TiXmlDeclaration* Header = new TiXmlDeclaration("1.0", "UTF-8", "");
		Doc.LinkEndChild(Header);
		TiXmlElement* Root = new TiXmlElement("PROJECT");
		TiXmlElement* Ent = new TiXmlElement("entities");
		Root->LinkEndChild(Ent);
		//add all game objects
		for (GameObject* go : mSceneObjects)
		{
			TiXmlElement* GameObj = new TiXmlElement("gameobject");
			GameObj->SetAttribute("name", go->GetName().c_str());
			TiXmlElement* components = new TiXmlElement("components");
			GameObj->LinkEndChild(components);
			for (Component* Comp : go->GetComponents())
			{
				switch (Comp->GetType())
				{
				case  COMPONENT_TRANSFORM:
				{
					TiXmlElement* Transform = new TiXmlElement("transform");
					Transform->SetAttribute("PosX", go->GetComponent<TransformComp>()->GetPosition().x);
					Transform->SetAttribute("PosY", go->GetComponent<TransformComp>()->GetPosition().y);

					Transform->SetAttribute("RotX", go->GetComponent<TransformComp>()->GetRotation().x);
					Transform->SetAttribute("RotY", go->GetComponent<TransformComp>()->GetRotation().y);

					Transform->SetAttribute("ScaleX", go->GetComponent<TransformComp>()->GetScale().x);
					Transform->SetAttribute("ScaleY", go->GetComponent<TransformComp>()->GetScale().x);

					components->LinkEndChild(Transform);
					break;
				}
				case COMPONENT_SPRITE:
				{
					TiXmlElement* Sprite = new TiXmlElement("sprite");
					Sprite->SetAttribute("path", go->GetComponent<SpriteComp>()->getpath().c_str());
					Sprite->SetAttribute("Colour", "0 0 0 0");

					int flipX = 0, flipY = 0;
					if (go->GetComponent<SpriteComp>()->GetFlipX())
					{
						flipX = 1;
					}
					if (go->GetComponent<SpriteComp>()->GetFlipY())
					{
						flipY = 1;
					}
					Sprite->SetAttribute("FlipX", flipX);
					Sprite->SetAttribute("FlipY", flipY);
					components->LinkEndChild(Sprite);
					break;
				}
				case COMPONENT_PHYSICS:
				{
					TiXmlElement* physics = new TiXmlElement("physics");

					components->LinkEndChild(physics);
					break;
				}
				case COMPONENT_SCRIPT:
				{
					TiXmlElement* script = new TiXmlElement("script");
					script->SetAttribute("path", go->GetComponent<ScriptComp>()->getpath().c_str());

					components->LinkEndChild(script);
					break;
				}
				case COMPONENT_TILEMAP:
				{
					TiXmlElement* tileMap = new TiXmlElement("tilemap");
					tileMap->SetAttribute("path", go->GetComponent<TileMapComp>()->getpath().c_str());

					components->LinkEndChild(tileMap);
					break;
				}
				default:
				{
					break;
				}
				}
				//add childeren
			}
			Ent->LinkEndChild(GameObj);
		}

		Doc.LinkEndChild(Root);
		if (!Doc.SaveFile(path.c_str()));
		{
			std::cerr << Doc.ErrorDesc() << std::endl;
		}

		// TODO:
		// Lots of pointers left here should clean them up when done with them
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

	void SceneManager::DestroyObject(GameObject* go)
	{
		auto index = std::find_if(mSceneObjects.begin(), mSceneObjects.end(),
			[&](const GameObject* object) {return go == object; });

		if (index != mSceneObjects.end())
		{
			GameObject* objectToDelete = mSceneObjects.at(std::distance(mSceneObjects.begin(), index));
			mSceneObjects.erase(index);

			if (objectToDelete->GetParent() != nullptr)
			{
				objectToDelete->GetParent()->RemoveChild(objectToDelete);
			}

			for (GameObject* child : objectToDelete->GetChildren())
			{
				DestroyObject(child);
			}

			delete objectToDelete;
			objectToDelete = nullptr;
		}
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
