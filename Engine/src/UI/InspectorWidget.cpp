#include "InspectorWidget.h"

#include "imgui.h"
#include "imgui_stdlib.h"

#include "ImFileDialog\ImFileDialog.h"

#include "Entities/GameObject.h"
#include "SceneManager.h"
#include "SceneHierarchyWidget.h"

namespace Engine
{
	void InspectorWidget::Render(GameObject* go)
	{
		ImGui::Begin("Inspector");

		if (go != nullptr)
		{
			std::string name = go->GetName();
			
			ImGui::InputText("###name", &name);

			ImGui::SameLine();

			if (ImGui::Button("Delete"))
			{
				SceneManager::GetInstance()->DestroyObject(go);
				go = nullptr;
				SceneHierarchyWidget::ClearNode();
				ImGui::End();
				return;
			}

			for (Component* c : go->GetComponents())
			{
				bool close = true;
				
				ImGui::PushID(c->GetID());

				switch (c->GetType())
				{
				case COMPONENT_TRANSFORM:
					if (ImGui::CollapsingHeader("Transform"))
					{
						RenderTransformComponent(dynamic_cast<TransformComp*>(c));
					}
					break;

				case COMPONENT_SPRITE:
					if (ImGui::CollapsingHeader("Sprite", &close))
					{
						RenderSpriteComponent(dynamic_cast<SpriteComp*>(c));
					}
					break;

				case COMPONENT_PHYSICS:
					if (ImGui::CollapsingHeader("Physics", &close))
					{
						RenderPhysicsComponent(dynamic_cast<PhysicsComp*>(c));
					}
					break;

				case COMPONENT_SCRIPT:
					if (ImGui::CollapsingHeader("Script", &close))
					{
						RenderScriptComponent(dynamic_cast<ScriptComp*>(c));
					}
					break;

				case COMPONENT_AUDIO:
					if (ImGui::CollapsingHeader("Audio", &close))
					{
					}
					break;

				case COMPONENT_CAMERA:
					if (ImGui::CollapsingHeader("Camera", &close))
					{
						RenderCameraComponent(dynamic_cast<CameraComp*>(c));
					}
					break;

				case COMPONENT_TILEMAP:
					if (ImGui::CollapsingHeader("TileMap", &close))
					{
						RenderTileMapComponent(dynamic_cast<TileMapComp*>(c));
					}
					break;

				case COMPONENT_COLBOX:
					if (ImGui::CollapsingHeader("Box Collision", &close))
					{
						RenderBoxColComponent(dynamic_cast<ObjectCollisionComp*>(c));
					}
					break;

				case COMPONENT_COLTILE:
					if (ImGui::CollapsingHeader("Tilemap Collision", &close))
					{
						RenderTilemapColComponent(dynamic_cast<TilemapCollisionComp*>(c));
					}
					break;

				case COMPONENT_COLLINE:
					if (ImGui::CollapsingHeader("Line Collision", &close))
					{
						RenderLineColComponent(dynamic_cast<LineCollisionComp*>(c));
					}
					break;
				default:
					break;
				}

				if (!close)
				{
					c->GetGameObject()->RemoveComponent(c);
					close = true;
				}

				ImGui::PopID();
			}

			ImGui::Separator();

			const char* comps[] = { "Sprite", "Script", "Audio", "Camera", "TileMap", "Physics", "Box Collision", "Tilemap Collision", "Line Collision" };

			if (ImGui::Button("Add Component..", ImVec2(ImGui::GetContentRegionAvail().x, 0.0f)))
			{
				ImGui::OpenPopup("CompList");
			}

			ImGui::SameLine();
			if (ImGui::BeginPopup("CompList"))
			{
				ImGui::Text("Components");
				ImGui::Separator();
				for (int i = 0; i < IM_ARRAYSIZE(comps); i++)
					if (ImGui::Selectable(comps[i]))
					{
						switch (i + 1)
						{
						case COMPONENT_SPRITE:
							SceneHierarchyWidget::GetNode()->AddComponent<SpriteComp>(new SpriteComp);
							break;

						case COMPONENT_PHYSICS:
							SceneHierarchyWidget::GetNode()->AddComponent<PhysicsComp>(new PhysicsComp);
							break;

						case COMPONENT_SCRIPT:
							SceneHierarchyWidget::GetNode()->AddComponent<ScriptComp>(new ScriptComp);
							break;

						case COMPONENT_AUDIO:

							break;

						case COMPONENT_CAMERA:
							SceneHierarchyWidget::GetNode()->AddComponent<CameraComp>(new CameraComp);
							break;

						case COMPONENT_TILEMAP:
							SceneHierarchyWidget::GetNode()->AddComponent<TileMapComp>(new TileMapComp);
							break;

						case COMPONENT_COLBOX:
							SceneHierarchyWidget::GetNode()->AddComponent<ObjectCollisionComp>(new ObjectCollisionComp);
							break;

						case COMPONENT_COLTILE:
							if (SceneHierarchyWidget::GetNode()->GetComponent<TileMapComp>() != NULL)
							{
								SceneHierarchyWidget::GetNode()->AddComponent<TilemapCollisionComp>(new TilemapCollisionComp);
								break;
							}
							else
								break;

						case COMPONENT_COLLINE:
							SceneHierarchyWidget::GetNode()->AddComponent<LineCollisionComp>(new LineCollisionComp);
							break;

						default:
							break;
						}
					}
				ImGui::EndPopup();
			}

			if (!name.empty())
				go->SetName(name);
		}


		ImGui::End();
	}

	void InspectorWidget::RenderTransformComponent(TransformComp* c)
	{
		float position[2];
		position[0] = c->GetPosition().x;
		position[1] = c->GetPosition().y;

		float scale[2] = { c->GetScale().x, c->GetScale().y };

		float rotation[2] = { c->GetRotation().x, c->GetRotation().y };

		ImGui::PushID("position");

		ImGui::Columns(2);
		ImGui::Text("Position");
		ImGui::NextColumn();
		ImGui::DragFloat2("##position", &position[0], 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("rotation");

		ImGui::Columns(2);
		ImGui::Text("Rotation");
		ImGui::NextColumn();
		ImGui::DragFloat2("##rotation", &rotation[0], 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("scale");

		ImGui::Columns(2);
		ImGui::Text("Scale");
		ImGui::NextColumn();
		ImGui::DragFloat2("##scale", &scale[0], 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		c->SetPosition(vec2f(position[0], position[1]));
		c->SetRotation(vec2f(rotation[0], rotation[1]));
		c->SetScale(vec2f(scale[0], scale[1]));
	}

	void InspectorWidget::RenderSpriteComponent(SpriteComp* c)
	{
		ImGui::PushID("sprite");

		bool flipX = c->GetFlipX();
		bool flipY = c->GetFlipY();
		std::string path;

		auto& ref = c->GetColour();

		if (c->GetTexture())
			path = c->GetTexture()->GetPath();
		else
			path = "Empty";

		static ImVec4 colour = ImVec4(ref[0], ref[1],
			ref[2], ref[3]);

		if (path.find_last_of('\\') != std::string::npos)
			path = path.substr(path.find_last_of('\\'));
		else if (path.find_last_of('/') != std::string::npos)
			path = path.substr(path.find_last_of('/'));

		if (ImGui::Button(path.c_str()))
		{
			ifd::FileDialog::Instance().Open("Texture File Browser", "Change Sprite Texture", "Texture File (*.png){.png},.*");
		}

		if (ifd::FileDialog::Instance().IsDone("Texture File Browser"))
		{	
			if (ifd::FileDialog::Instance().HasResult())
				{
					std::string Texpath = ifd::FileDialog::Instance().GetResult().u8string();
					c->SetTexture(AssetManager::GetInstance()->LoadTexture(path, Texpath));
					int startPos = Texpath.find("Assets");
					Texpath.erase(0, startPos);
				}

			ifd::FileDialog::Instance().Close();
		}

		ImGui::SameLine();
		if (c->GetTexture())
			ImGui::Image((void*)(intptr_t)c->GetTexID(), ImVec2(32.0f, 32.0f));

		ImGui::Text("Color");
		ImGui::SameLine();
		ImGui::ColorEdit4("##colpicker", (float*)&colour, ImGuiColorEditFlags_NoDragDrop);

		ImGui::Columns(2);
		ImGui::Text("Flip");
		ImGui::NextColumn();
		ImGui::Checkbox("X", &flipX);
		ImGui::SameLine();
		ImGui::Checkbox("Y", &flipY);
		ImGui::Columns(1);

		c->ToggleFlipX(flipX);
		c->ToggleFlipY(flipY);
		c->SetColour(colour.x, colour.y, colour.z, colour.w);

		ImGui::PopID();
	}

	void InspectorWidget::RenderPhysicsComponent(PhysicsComp* c)
	{
		float physMass = c->GetMass();
		float physGrav = c->GetGravity();
		float physFric = c->GetFriction();
		float physMaxSpeed = c->GetMaxSpeed();

		vec2f physVelocity = c->GetVelocity();


		ImGui::PushID("mass");

		ImGui::Columns(2);
		ImGui::Text("Mass");
		ImGui::NextColumn();
		ImGui::DragFloat("##mass", &physMass, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("gravity");

		ImGui::Columns(2);
		ImGui::Text("Gravity");
		ImGui::NextColumn();
		ImGui::DragFloat("##gravity", &physGrav, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("friction");

		ImGui::Columns(2);
		ImGui::Text("Friction");
		ImGui::NextColumn();
		ImGui::DragFloat("##friction", &physFric, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();


		ImGui::PushID("max speed");

		ImGui::Columns(2);
		ImGui::Text("Max Speed");
		ImGui::NextColumn();
		ImGui::DragFloat("##max speed", &physMaxSpeed, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();


		ImGui::PushID("velocity");

		ImGui::Columns(2);
		ImGui::Text("Velocity");
		ImGui::NextColumn();
		ImGui::Text("X: %.2f", physVelocity.x);
		ImGui::SameLine();
		ImGui::Text("Y: %.2f", physVelocity.y);
		ImGui::Columns(1);

		ImGui::PopID();

		c->SetMass(physMass);
		c->SetGravity(physGrav);
		c->SetFriction(physFric);
		c->SetMaxSpeed(physMaxSpeed);
	}

	void InspectorWidget::RenderScriptComponent(ScriptComp* c)
	{
		ImGui::PushID("script");

		std::string path = c->GetFile();
		if (path.empty())
			path = "None";

		if (path.find_last_of('\\') != std::string::npos)
			path = path.substr(path.find_last_of('\\'));
		else if (path.find_last_of('/') != std::string::npos)
			path = path.substr(path.find_last_of('/'));

		if (ImGui::Button(path.c_str()))
		{
			ifd::FileDialog::Instance().Open("Script File Browser", "Change Script File", "Script File (*.lua){.lua},.*");
		}

		if (ifd::FileDialog::Instance().IsDone("Script File Browser"))
		{
			if (ifd::FileDialog::Instance().HasResult() && ifd::FileDialog::Instance().GetResult().u8string() != c->GetFile())
			{
				c->RemoveScript();
				std::string Scriptpath = ifd::FileDialog::Instance().GetResult().u8string();
				c->AddScript(Scriptpath);
				int startPos = Scriptpath.find("Assets");
				Scriptpath.erase(0, startPos);
				c->Setpath(Scriptpath);
			}
			ifd::FileDialog::Instance().Close();
		}

		ImGui::PopID();
	}

	void InspectorWidget::RenderTileMapComponent(TileMapComp* c)
	{
		ImGui::PushID("TileMap");

		ImGui::Begin("Tile Editor");
		/*static int selectionMask = (1 << 2);
		int sceneIndex = 0;
		int nodeClicked = -1;*/
		static int TileID;

		for (int i = 0; i < c->GetTextures().size(); i++) {
			auto tex = c->GetTextures().at(i);
			ImGui::PushID(i);
			if (ImGui::ImageButton((void*)(intptr_t)tex->GetTexID(), ImVec2(tex->GetWidth(), tex->GetHeight())))
			{
				TileID = i;

			}
			ImGui::SameLine();
			ImGui::PopID();

			

			if (ImGui::GetIO().MouseDown[1])
			{
				//TODO change mousepos to use world pos of camera 
				vec2f mousePos = vec2f(InputManager::GetInstance()->GetMouseScreenPosition().x, InputManager::GetInstance()->GetMouseScreenPosition().y);
				mousePos.x /= InputManager::GetInstance()->GetScreenSizePercent().x;
				mousePos.y /= InputManager::GetInstance()->GetScreenSizePercent().y;

				vec2f screenSize = InputManager::GetInstance()->GetScreenSize();

				mousePos.x -= c->GetGameObject()->GetComponent<TransformComp>()->GetPosition().x;
				mousePos.y -= c->GetGameObject()->GetComponent<TransformComp>()->GetPosition().y;

				glm::vec4 CameraPos = CameraManager::Get()->GetPrimaryCamera()->GetAt();
				mousePos.x += (CameraPos.x - 630);
				mousePos.y -= (CameraPos.y + 338);

				c->ChangeTile(TileID, vec2i((mousePos.y / TILEHEIGHT), (mousePos.x / TILEWIDTH)));
			}

		}
		ImGui::End();

		//Load TileMap
		//----------------------------------------------------------------------------------------------
		if (ImGui::Button("Load TileMap"))
		{
			ifd::FileDialog::Instance().Open("TileMapLoader", "LoadTileMap", "TileMap (*.xml){.xml},.*");
		}

		if (ifd::FileDialog::Instance().IsDone("TileMapLoader"))
		{
			if (ifd::FileDialog::Instance().HasResult())
			{
				std::string TempString = ifd::FileDialog::Instance().GetResult().u8string();
				int startPos = TempString.find("Assets");
				TempString.erase(0, startPos);
				c->LoadTileMap(TempString.c_str());
				c->Setpath(TempString);
				//TileMap temp = c->GetTileMap();
			}
			ifd::FileDialog::Instance().Close();
		}
		//----------------------------------------------------------------------------------------------

		//Save TileMap
		//----------------------------------------------------------------------------------------------
		if (ImGui::Button("Save TileMap"))
		{
			ifd::FileDialog::Instance().Save("TileMapSaver", "SaveTileMap", "TileMap (*.xml) {.xml}, .*");
		}

		if (ifd::FileDialog::Instance().IsDone("TileMapSaver"))
		{
			if (ifd::FileDialog::Instance().HasResult())
			{
				std::string TempString = ifd::FileDialog::Instance().GetResult().u8string();
				int startPos = TempString.find("Assets");
				TempString.erase(0, startPos);
				c->SaveTileMap(TempString, vec2i(c->GetTileMap().size(), c->GetTileMap()[0].size()));
				c->Setpath(TempString);
			}
			ifd::FileDialog::Instance().Close();
		}
		//----------------------------------------------------------------------------------------------

		ImGui::PopID();
	}

	void InspectorWidget::RenderCameraComponent(CameraComp* c)
	{
		float fov = c->GetFOV();
		float cNear = c->GetNear(); // camera near clipping
		float cFar = c->GetFar(); // camera far clipping
		float depth = c->GetDepth();

		ImGui::PushID("fov");

		ImGui::Columns(2);
		ImGui::Text("FOV");
		ImGui::NextColumn();
		ImGui::DragFloat("##friction", &fov, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("near");

		ImGui::Columns(2);
		ImGui::Text("Near");
		ImGui::NextColumn();
		ImGui::DragFloat("##near", &cNear, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("far");

		ImGui::Columns(2);
		ImGui::Text("Far");
		ImGui::NextColumn();
		ImGui::DragFloat("##far", &cFar, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("depth");

		ImGui::Columns(2);
		ImGui::Text("Depth");
		ImGui::NextColumn();
		ImGui::DragFloat("##depth", &depth, 0.1f);
		ImGui::Columns(1);

		ImGui::PopID();

		if (cFar > cNear)
		c->SetFar(cFar);

		c->SetFOV(fov);

		if (cNear > 0.1f && cFar > cNear)
		c->SetNear(cNear);

		c->SetDepth(depth);
	}

	void InspectorWidget::RenderBoxColComponent(ObjectCollisionComp* c)
	{
		Box2D colBox = c->GetColBox();
		float colBoxSize[2] = { colBox.GetSize().x, colBox.GetSize().y };
		float boundSize = c->GetBRange();
		bool isSolid = c->GetColToggle();
		bool isTrigger = c->GetTrigger();

		ImGui::PushID("Size");

		ImGui::Columns(2);
		ImGui::Text("Size");
		ImGui::NextColumn();
		ImGui::DragFloat2("##size", &colBoxSize[0], 1.0f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Bounding");

		ImGui::Columns(2);
		ImGui::Text("Bounding");
		ImGui::NextColumn();
		ImGui::DragFloat("##bounding", &boundSize, 1.0f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Solid");

		ImGui::Columns(2);
		ImGui::Text("Solid");
		ImGui::NextColumn();
		ImGui::Checkbox("Is Solid?", &isSolid);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Trigger");

		ImGui::Columns(2);
		ImGui::Text("Trigger");
		ImGui::NextColumn();
		ImGui::Checkbox("Is Trigger?", &isTrigger);
		ImGui::Columns(1);

		ImGui::PopID();

		c->GetColBox().SetSize(vec2f(colBoxSize[0], colBoxSize[1]));
		c->SetBRange(boundSize);
		c->SetColToggle(isSolid);
		c->SetTrigger(isTrigger);
	}

	void InspectorWidget::RenderLineColComponent(LineCollisionComp* c)
	{
		float point1[2] = { c->GetPoint1().x, c->GetPoint1().y };
		float point2[2] = { c->GetPoint2().x, c->GetPoint2().y };
		bool isSolid = c->GetColToggle();
		bool isTrigger = c->GetTrigger();

		ImGui::PushID("Point 1");

		ImGui::Columns(2);
		ImGui::Text("Point 1");
		ImGui::NextColumn();
		ImGui::DragFloat2("##point 1", &point1[0], 1.0f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Point 2");

		ImGui::Columns(2);
		ImGui::Text("Point 2");
		ImGui::NextColumn();
		ImGui::DragFloat2("##point 2", &point2[0], 1.0f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Solid");

		ImGui::Columns(2);
		ImGui::Text("Solid");
		ImGui::NextColumn();
		ImGui::Checkbox("Is Solid?", &isSolid);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Trigger");

		ImGui::Columns(2);
		ImGui::Text("Trigger");
		ImGui::NextColumn();
		ImGui::Checkbox("Is Trigger?", &isTrigger);
		ImGui::Columns(1);

		ImGui::PopID();

		c->SetPoint1(vec2f(point1[0], point1[1]));
		c->SetPoint2(vec2f(point2[0], point2[1]));
		c->SetColToggle(isSolid);
		c->SetTrigger(isTrigger);
	}

	void InspectorWidget::RenderTilemapColComponent(TilemapCollisionComp* c)
	{
		float boundSize = c->GetBRange();
		bool isSolid = c->GetColToggle();
		bool isTrigger = c->GetTrigger();

		ImGui::PushID("Bounding");

		ImGui::Columns(2);
		ImGui::Text("Bounding");
		ImGui::NextColumn();
		ImGui::DragFloat("##bounding", &boundSize, 1.0f);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Solid");

		ImGui::Columns(2);
		ImGui::Text("Solid");
		ImGui::NextColumn();
		ImGui::Checkbox("Is Solid?", &isSolid);
		ImGui::Columns(1);

		ImGui::PopID();

		ImGui::PushID("Trigger");

		ImGui::Columns(2);
		ImGui::Text("Trigger");
		ImGui::NextColumn();
		ImGui::Checkbox("Is Trigger?", &isTrigger);
		ImGui::Columns(1);

		ImGui::PopID();

		c->SetBRange(boundSize);
		c->SetColToggle(isSolid);
		c->SetTrigger(isTrigger);

		if (ImGui::Button("Refresh Collision Boxes"))
		{
			c->RefreshTileBoxes();
		}
	}

	InspectorWidget::InspectorWidget()
	{
	}
	InspectorWidget::~InspectorWidget()
	{
	}
}