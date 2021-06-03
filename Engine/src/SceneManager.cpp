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

		auto camera = CameraManager::Get()->Add(vec2f((1260/2), -(677/2)), true);		// Camera manager deletes its cameras, no mem leak :)         
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

		mUnsavedChanges = false;
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
				TransformComp* Transform = NewObject->GetComponent<TransformComp>();
				//Position / Rotation / scale

				//get pos
				vec2f Pos;
				Pos.x = atof(CurrentComp->Attribute("PosX"));
				Pos.y = atof(CurrentComp->Attribute("PosY"));
				//set Pos to newobject				
				Transform->SetPosition(Pos);

				//get rotation
				vec2f Rot;
				Rot.x = atof(CurrentComp->Attribute("RotX"));
				Rot.y = atof(CurrentComp->Attribute("RotY"));

				Transform->SetRotation(Rot);

				vec2f Scale;
				Scale.x = atof(CurrentComp->Attribute("ScaleX"));
				Scale.y = atof(CurrentComp->Attribute("ScaleY"));

				Transform->SetScale(Scale);				
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
				}
				//Colour
				float colour[4];
				std::string Colour = CurrentComp->Attribute("Colour");

				std::stringstream ss(Colour);
				float n; int m = 0;
				while (ss >> n)
				{
					colour[m] = n;
					m++;
				}	

				NewSprite->SetColour(colour[0], colour[1], colour[2], colour[3]);
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
			else if (CompType == "audio")
			{
				//this dont work 
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
			else if (CompType == "physics")
			{
				PhysicsComp* NewPhysics = NewObject->AddComponent<PhysicsComp>(new PhysicsComp);
				NewPhysics->SetMass(atof(CurrentComp->Attribute("Mass")));
				NewPhysics->SetGravity(atof(CurrentComp->Attribute("Gravity")));
				NewPhysics->SetFriction(atof(CurrentComp->Attribute("Friction")));
				NewPhysics->SetMaxSpeed(atof(CurrentComp->Attribute("MaxSpeed")));

			}
			else if (CompType == "boxcol")
			{
				ObjectCollisionComp* NewBoxCol = NewObject->AddComponent<ObjectCollisionComp>(new ObjectCollisionComp);
				float sizex, sizey;
				sizex = atof(CurrentComp->Attribute("SizeX"));
				sizey = atof(CurrentComp->Attribute("SizeY"));
				NewBoxCol->GetColBox().SetSize(vec2f(sizex, sizey));
				NewBoxCol->SetBRange(atof(CurrentComp->Attribute("Bounding")));

			}
			else if (CompType == "tilecol")
			{
				TilemapCollisionComp* NewTileCol = NewObject->AddComponent<TilemapCollisionComp>(new TilemapCollisionComp);
				NewTileCol->SetBRange(atof(CurrentComp->Attribute("Bounding")));
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
			}
			else if (CompType == "particleSystem")
			{
			ParticleComp* comp = NewObject->AddComponent<ParticleComp>(new ParticleComp(NewObject));

			switch (atoi(CurrentComp->Attribute("Emitter"))) {
			case 0:
				comp->SetEmmitter(Emmitter::Square);
				break;
			case 1:
				comp->SetEmmitter(Emmitter::Circle);
				break;
			case 2:
				comp->SetEmmitter(Emmitter::Cone);
				break;
			}

			switch (atoi(CurrentComp->Attribute("Style"))) {
			case 0:
				comp->SetParticleTex(ParticleTexture::Custom);
				break;
			case 1:
				comp->SetParticleTex(ParticleTexture::Circle);
				break;
			case 2:
				comp->SetParticleTex(ParticleTexture::Square);
				break;
			case 3:
				comp->SetParticleTex(ParticleTexture::Triangle);
				break;
			}


			comp->SetParticleCount(atof(CurrentComp->Attribute("Count")));
			comp->SetRate(atof(CurrentComp->Attribute("Rate")));
			comp->SetLifetime(atof(CurrentComp->Attribute("Lifetime")));
			comp->SetGravity(atof(CurrentComp->Attribute("Gravity")));
			vec2f vel;
			vel.x = atof(CurrentComp->Attribute("VelocityX"));
			vel.y = atof(CurrentComp->Attribute("VelocityY"));
			comp->SetVelocity(vel);
			comp->SetColour(glm::vec4{ atof(CurrentComp->Attribute("ColorR")), atof(CurrentComp->Attribute("ColorG")),  atof(CurrentComp->Attribute("ColorB")), atof(CurrentComp->Attribute("ColorA")) });
			const char* t = CurrentComp->Attribute("TexPath");
			comp->SetParticleTexPath(t);

			vec2f size;
			size.x = atof(CurrentComp->Attribute("SizeX"));
			size.y = atof(CurrentComp->Attribute("SizeY"));
			comp->SetSize(size);

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

		mUnsavedChanges = false;
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
				Transform->SetDoubleAttribute("PosX", CurrentGameObj->GetComponent<TransformComp>()->GetPosition().x);
				Transform->SetDoubleAttribute("PosY", CurrentGameObj->GetComponent<TransformComp>()->GetPosition().y);

				Transform->SetDoubleAttribute("RotX", CurrentGameObj->GetComponent<TransformComp>()->GetRotation().x);
				Transform->SetDoubleAttribute("RotY", CurrentGameObj->GetComponent<TransformComp>()->GetRotation().y);

				Transform->SetDoubleAttribute("ScaleX", CurrentGameObj->GetComponent<TransformComp>()->GetScale().x);
				Transform->SetDoubleAttribute("ScaleY", CurrentGameObj->GetComponent<TransformComp>()->GetScale().x);

				components->LinkEndChild(Transform);
				break;
			}
			case COMPONENT_SPRITE:
			{
				TiXmlElement* Sprite = new TiXmlElement("sprite");
				Sprite->SetAttribute("path", CurrentGameObj->GetComponent<SpriteComp>()->GetTexture()->GetPath().c_str());
				char Colour[50];
				std::sprintf(Colour, "%f %f %f %f", CurrentGameObj->GetComponent<SpriteComp>()->GetColour()[0], CurrentGameObj->GetComponent<SpriteComp>()->GetColour()[1], CurrentGameObj->GetComponent<SpriteComp>()->GetColour()[2], CurrentGameObj->GetComponent<SpriteComp>()->GetColour()[3]);
				Sprite->SetAttribute("Colour", Colour);

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
			case COMPONENT_SCRIPT:
			{
				TiXmlElement* script = new TiXmlElement("script");
				script->SetAttribute("path", CurrentGameObj->GetComponent<ScriptComp>()->getpath().c_str());

				components->LinkEndChild(script);
				break;
			}
			case COMPONENT_AUDIO:
			{
				break;
			}
			case COMPONENT_CAMERA:
			{
				//FOV / Near / Far / Depth
				TiXmlElement* Camera = new TiXmlElement("camera");
				Camera->SetDoubleAttribute("FOV", CurrentGameObj->GetComponent<CameraComp>()->GetFOV());
				Camera->SetDoubleAttribute("Near", CurrentGameObj->GetComponent<CameraComp>()->GetNear());
				Camera->SetDoubleAttribute("Far", CurrentGameObj->GetComponent<CameraComp>()->GetFar());
				Camera->SetDoubleAttribute("Depth", CurrentGameObj->GetComponent<CameraComp>()->GetDepth());
				components->LinkEndChild(Camera);
				break;
			}
			case COMPONENT_TILEMAP:
			{
				TiXmlElement* tileMap = new TiXmlElement("tilemap");
				tileMap->SetAttribute("path", CurrentGameObj->GetComponent<TileMapComp>()->getpath().c_str());

				components->LinkEndChild(tileMap);
				break;
			}
			case COMPONENT_PHYSICS:
			{
				TiXmlElement* physics = new TiXmlElement("physics");
				physics->SetDoubleAttribute("Mass", CurrentGameObj->GetComponent<PhysicsComp>()->GetMass());
				physics->SetDoubleAttribute("Gravity", CurrentGameObj->GetComponent<PhysicsComp>()->GetGravity());
				physics->SetDoubleAttribute("Friction", CurrentGameObj->GetComponent<PhysicsComp>()->GetFriction());
				physics->SetDoubleAttribute("MaxSpeed", CurrentGameObj->GetComponent<PhysicsComp>()->GetMaxSpeed());

				components->LinkEndChild(physics);
				break;
			}
			case COMPONENT_COLBOX:
			{
				TiXmlElement* BoxCol = new TiXmlElement("boxcol");
				BoxCol->SetDoubleAttribute("SizeX", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetColBox().GetSize().x);
				BoxCol->SetDoubleAttribute("SizeY", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetColBox().GetSize().y);
				BoxCol->SetDoubleAttribute("Bounding", CurrentGameObj->GetComponent<ObjectCollisionComp>()->GetBRange());

				components->LinkEndChild(BoxCol);
				break;
			}
			case COMPONENT_COLTILE:
			{
				TiXmlElement* TileCol = new TiXmlElement("tilecol");
				TileCol->SetDoubleAttribute("Bounding", CurrentGameObj->GetComponent<TilemapCollisionComp>()->GetBRange());

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

				components->LinkEndChild(LineCol);
				break;
			}
			case COMPONENT_PARTICLE:
			{
				TiXmlElement* xml = new TiXmlElement("particleSystem");
				ParticleComp* sys = CurrentGameObj->GetComponent<ParticleComp>();
				xml->SetAttribute("Emitter", (int)sys->GetEmmitter());
				xml->SetAttribute("Style", (int)sys->GetParticleTexture());
				xml->SetAttribute("Count", sys->GetParticleCount());
				xml->SetDoubleAttribute("Rate", sys->GetRate());
				xml->SetDoubleAttribute("Lifetime", sys->GetLifetime());
				xml->SetDoubleAttribute("Gravity", sys->GetGravity());
				xml->SetDoubleAttribute("VelocityX", sys->GetVelocity().x);
				xml->SetDoubleAttribute("VelocityY", sys->GetVelocity().y);
				xml->SetDoubleAttribute("ColorR", sys->GetColour().r);
				xml->SetDoubleAttribute("ColorG", sys->GetColour().g);
				xml->SetDoubleAttribute("ColorB", sys->GetColour().b);
				xml->SetDoubleAttribute("ColorA", sys->GetColour().a);

				if (!sys->GetTexturePath().empty()) {
					xml->SetAttribute("TexPath", sys->GetTexturePath().c_str());
				} 
				else
					xml->SetAttribute("TexPath", "");

				xml->SetDoubleAttribute("SizeX", sys->GetSize().x);
				xml->SetDoubleAttribute("SizeY", sys->GetSize().y);

				components->LinkEndChild(xml);
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

		mUnsavedChanges = true;
	}

	GameObject* SceneManager::CreateObject()
	{
		GameObject* go = new GameObject();
		mSceneObjects.push_back(go);
		mCounter++;
		go->SetName("Unnamed Object " + std::to_string(mCounter));

		mUnsavedChanges = true;

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

			mUnsavedChanges = true;
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
