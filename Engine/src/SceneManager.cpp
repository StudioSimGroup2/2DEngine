#include "SceneManager.h"
#include "Scripting\ScriptingEngine.h"
#include "CameraManager.h"
#include "Collision.h"

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
						}
						else
						{
							go->GetComponent<Engine::PhysicsComp>()->SetGrounded(false);
						}

						if (Collision::CheckTrigger(go, compObj))
						{
							Logger::LogMsg("Trigger");
						}
					}
				}
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
			TiXmlElement* Entities = root->FirstChildElement();
			//Loop through all GameObjects
			for (TiXmlElement* CurrentObject = Entities->FirstChildElement(); CurrentObject != NULL; CurrentObject = CurrentObject->NextSiblingElement())
			{
				LoadObject(CurrentObject, nullptr);

			}
			// TODO:
			// Lots of pointers left here should clean them up when done with them
		}
	}

	void SceneManager::LoadObject(TiXmlElement* CurrentObject, GameObject* ParentObj)
	{
		GameObject* NewObject = CreateObject();
		if (ParentObj != nullptr)
		{
			NewObject->Attach(ParentObj);
		}

		NewObject->SetName(CurrentObject->Attribute("name"));
		TiXmlElement* comps = CurrentObject->FirstChildElement("components");
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
				SpriteComp* NewSprite = NewObject->AddComponent<SpriteComp>(new SpriteComp);
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
			}
			else if (CompType == "physics")
			{
				//mass / gravity / friction
				PhysicsComp* NewPhysics = NewObject->AddComponent<PhysicsComp>(new PhysicsComp);
			}
			else if (CompType == "script")
			{
				//Path
				ScriptComp* NewScript = NewObject->AddComponent<ScriptComp>(new ScriptComp);
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
				TileMapComp* NewtileMap = NewObject->AddComponent<TileMapComp>(new TileMapComp);
				std::string path = CurrentComp->Attribute("path");
				if (path != "")
				{
					NewtileMap->LoadTileMap(path);
					NewtileMap->Setpath(path);
				}
			}
			else if (CompType == "camera")
			{
				int i = 0;
				CameraComp* NewCamera = NewObject->AddComponent<CameraComp>(new CameraComp);
				NewCamera->SetFOV(atof(CurrentComp->Attribute("FOV")));
				NewCamera->SetNear(atof(CurrentComp->Attribute("Near")));
				NewCamera->SetFar(atof(CurrentComp->Attribute("Far")));
				NewCamera->SetDepth(atof(CurrentComp->Attribute("Depth")));
			}
			else if (CompType == "boxcol")
			{
				ObjectCollisionComp* NewBoxCol = NewObject->AddComponent<ObjectCollisionComp>(new ObjectCollisionComp);
				float sizex, sizey;
				sizex = atof(CurrentComp->Attribute("SizeX"));
				sizey = atof(CurrentComp->Attribute("SizeY"));
				NewBoxCol->GetColBox().SetSize(vec2f(sizex, sizey));
				NewBoxCol->SetBRange(atof(CurrentComp->Attribute("Bounding")));
				NewBoxCol->SetColToggle(atof(CurrentComp->Attribute("Solid")));
				NewBoxCol->SetTrigger(atof(CurrentComp->Attribute("Trigger")));
			}
			else if (CompType == "tilecol")
			{
				TilemapCollisionComp* NewTileCol = NewObject->AddComponent<TilemapCollisionComp>(new TilemapCollisionComp);
				NewTileCol->SetBRange(atof(CurrentComp->Attribute("Bounding")));
				NewTileCol->SetColToggle(atof(CurrentComp->Attribute("Solid")));
				NewTileCol->SetTrigger(atof(CurrentComp->Attribute("Trigger")));
			}
			else if (CompType == "linecol")
			{
				LineCollisionComp* NewLineCol = NewObject->AddComponent<LineCollisionComp>(new LineCollisionComp);
				float p1x, p1y, p2x, p2y;
				p1x = atof(CurrentComp->Attribute("Point1X"));
				p1y = atof(CurrentComp->Attribute("Point1Y"));
				p2x = atof(CurrentComp->Attribute("Point2X"));
				p2y = atof(CurrentComp->Attribute("Point2Y"));

				NewLineCol->SetPoint1(vec2f(p1x, p1y));
				NewLineCol->SetPoint2(vec2f(p2x, p2y));
				NewLineCol->SetBRange(atof(CurrentComp->Attribute("Bounding")));
				NewLineCol->SetColToggle(atof(CurrentComp->Attribute("Solid")));
				NewLineCol->SetTrigger(atof(CurrentComp->Attribute("Trigger")));
			}
		}
		TiXmlElement* Children = CurrentObject->FirstChildElement("children");
		if (Children != NULL)
		{
			for (TiXmlElement* CurrentChildren = Children->FirstChildElement(); CurrentChildren != NULL; CurrentChildren = CurrentChildren->NextSiblingElement())
			{
				TiXmlElement* Child = Children->FirstChildElement();
				LoadObject(Child, NewObject);
			}
		}
	}

	void SceneManager::SaveScene(std::string path)
	{
		//Save scene to an XML file for later loading
		TiXmlDocument Doc;
		TiXmlDeclaration* Header = new TiXmlDeclaration("1.0", "UTF-8", "");
		Doc.LinkEndChild(Header);
		TiXmlElement* Root = new TiXmlElement("PROJECT");
		TiXmlElement* Ent = new TiXmlElement("entities");
		Root->LinkEndChild(Ent);


		//add all game objects
		for (GameObject* go : mSceneObjects)
		{
			if (go->GetParent() == nullptr)
			{
				TiXmlElement* GameObj = new TiXmlElement("gameobject");
				GameObj->SetAttribute("name", go->GetName().c_str());
				SaveObject(GameObj, go);
				Ent->LinkEndChild(GameObj);
			}			
		}

		Doc.LinkEndChild(Root);
		if (!Doc.SaveFile(path.c_str()));
		{
			std::cerr << Doc.ErrorDesc() << std::endl;
		}

		// TODO:
		// Lots of pointers left here should clean them up when done with them
	}

	void SceneManager::SaveObject(TiXmlElement* GameObj, GameObject* CurrentGameObj)
	{
		TiXmlElement* components = new TiXmlElement("components");
		GameObj->LinkEndChild(components);
		//Loop through all the components of a game object and add them as node to a XML file
		for (Component* Comp : CurrentGameObj->GetComponents())
		{
			switch (Comp->GetType())
			{
			case  COMPONENT_TRANSFORM:
			{
				TiXmlElement* Transform = new TiXmlElement("transform");
				Transform->SetAttribute("PosX", CurrentGameObj->GetComponent<TransformComp>()->GetPosition().x);
				Transform->SetAttribute("PosY", CurrentGameObj->GetComponent<TransformComp>()->GetPosition().y);

				Transform->SetAttribute("RotX", CurrentGameObj->GetComponent<TransformComp>()->GetRotation().x);
				Transform->SetAttribute("RotY", CurrentGameObj->GetComponent<TransformComp>()->GetRotation().y);

				Transform->SetAttribute("ScaleX", CurrentGameObj->GetComponent<TransformComp>()->GetScale().x);
				Transform->SetAttribute("ScaleY", CurrentGameObj->GetComponent<TransformComp>()->GetScale().x);

				components->LinkEndChild(Transform);
				break;
			}
			case COMPONENT_SPRITE:
			{
				TiXmlElement* Sprite = new TiXmlElement("sprite");
				Sprite->SetAttribute("path", CurrentGameObj->GetComponent<SpriteComp>()->getpath().c_str());
				Sprite->SetAttribute("Colour", "0 0 0 0");

				int flipX = 0, flipY = 0;
				if (CurrentGameObj->GetComponent<SpriteComp>()->GetFlipX())
				{
					flipX = 1;
				}
				if (CurrentGameObj->GetComponent<SpriteComp>()->GetFlipY())
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
				script->SetAttribute("path", CurrentGameObj->GetComponent<ScriptComp>()->getpath().c_str());

				components->LinkEndChild(script);
				break;
			}
			case COMPONENT_TILEMAP:
			{
				TiXmlElement* tileMap = new TiXmlElement("tilemap");
				tileMap->SetAttribute("path", CurrentGameObj->GetComponent<TileMapComp>()->getpath().c_str());

				components->LinkEndChild(tileMap);
				break;
			}
			case COMPONENT_CAMERA:
			{
				//FOV / Near / Far / Depth
				TiXmlElement* Camera = new TiXmlElement("camera");
				Camera->SetAttribute("FOV", CurrentGameObj->GetComponent<CameraComp>()->GetFOV());
				Camera->SetAttribute("Near", CurrentGameObj->GetComponent<CameraComp>()->GetNear());
				Camera->SetAttribute("Far", CurrentGameObj->GetComponent<CameraComp>()->GetFar());
				Camera->SetAttribute("Depth", CurrentGameObj->GetComponent<CameraComp>()->GetDepth());
				components->LinkEndChild(Camera);
				break;
			}
			case COMPONENT_COLBOX:
			{
				TiXmlElement* BoxCol = new TiXmlElement("boxcol");
				BoxCol->SetDoubleAttribute("SizeX", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetColBox().GetSize().x);
				BoxCol->SetDoubleAttribute("SizeY", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetColBox().GetSize().y);
				BoxCol->SetDoubleAttribute("Bounding", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetBRange());
				BoxCol->SetAttribute("Solid", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetColToggle());
				BoxCol->SetAttribute("Trigger", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetTrigger());


				components->LinkEndChild(BoxCol);
				break;
			}
			case COMPONENT_COLTILE:
			{
				TiXmlElement* TileCol = new TiXmlElement("tilecol");
				TileCol->SetDoubleAttribute("Bounding", CurrentGameObj->GetComponent<TilemapCollisionComp>()->GetBRange());
				TileCol->SetAttribute("Solid", CurrentGameObj->GetComponent<TilemapCollisionComp>()->GetColToggle());
				TileCol->SetAttribute("Trigger", CurrentGameObj->GetComponent<TilemapCollisionComp>()->GetTrigger());

				components->LinkEndChild(TileCol);
				break;
			}
			case COMPONENT_COLLINE:
			{
				TiXmlElement* LineCol = new TiXmlElement("linecol");
				LineCol->SetDoubleAttribute("Point1X", CurrentGameObj->GetComponent<LineCollisionComp>()->GetPoint1().x);
				LineCol->SetDoubleAttribute("Point1Y", CurrentGameObj->GetComponent<LineCollisionComp>()->GetPoint1().y);
				LineCol->SetDoubleAttribute("Point2X", CurrentGameObj->GetComponent<LineCollisionComp>()->GetPoint2().x);
				LineCol->SetDoubleAttribute("Point2Y", CurrentGameObj->GetComponent<LineCollisionComp>()->GetPoint2().y);
				LineCol->SetDoubleAttribute("Bounding", CurrentGameObj->GetComponent<LineCollisionComp>()->GetBRange());
				LineCol->SetAttribute("Solid", CurrentGameObj->GetComponent<LineCollisionComp>()->GetColToggle());
				LineCol->SetAttribute("Trigger", CurrentGameObj->GetComponent<LineCollisionComp>()->GetTrigger());

				components->LinkEndChild(LineCol);
				break;
			}
			default:
			{
				break;
			}
			}			
		}
		for (GameObject* go2 : CurrentGameObj->GetChildren())
		{
			//Loop through all the components of a game object and add them as node to a XML file
			TiXmlElement* Children = new TiXmlElement("children");
			GameObj->LinkEndChild(Children);

			TiXmlElement* ChildGameObj = new TiXmlElement("gameobject");
			ChildGameObj->SetAttribute("name", go2->GetName().c_str());
			SaveObject(ChildGameObj, go2);
			Children->LinkEndChild(ChildGameObj);
		}
	}

	void SceneManager::ClearScene()
	{
		mSceneObjects.clear();
	}

	GameObject* SceneManager::CreateObject()
	{
		GameObject* go = new GameObject();
		mSceneObjects.push_back(go);
		mCounter++;
		go->SetName("Unnamed Object " + std::to_string(mCounter));

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
