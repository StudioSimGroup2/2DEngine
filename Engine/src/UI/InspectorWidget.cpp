#include "InspectorWidget.h"

#include "imgui.h"

#include "Entities/GameObject.h"
#include "ImFileDialog\ImFileDialog.h"

namespace Engine
{
	void InspectorWidget::Render(GameObject* go)
	{
		ImGui::Begin("Inspector");

		if (go != nullptr)
		{
			ImGui::Text(go->GetName().c_str());

			for (Component* c : go->GetComponents())
			{
				switch (c->GetType())
				{
				case COMPONENT_TRANSFORM:
					if (ImGui::CollapsingHeader("Transform"))
					{
						RenderTransformComponent(dynamic_cast<TransformComp*>(c));
					}
					break;

				case COMPONENT_SPRITE:
					if (ImGui::CollapsingHeader("Sprite"))
					{
						RenderSpriteComponent(dynamic_cast<SpriteComp*>(c));
					}
					break;

				case COMPONENT_PHYSICS:
					if (ImGui::CollapsingHeader("Physics"))
					{
						RenderPhysicsComponent(dynamic_cast<PhysicsComp*>(c));
					}
					break;

				case COMPONENT_SCRIPT:
					if (ImGui::CollapsingHeader("Script"))
					{
						RenderScriptComponent(dynamic_cast<ScriptComp*>(c));
					}
					break;

				case COMPONENT_AUDIO:
					if (ImGui::CollapsingHeader("Audio"))
					{
					}
					break;

				case COMPONENT_CAMERA:
					if (ImGui::CollapsingHeader("Camera"))
					{
					}
					break;

				case COMPONENT_TILEMAP:
					if (ImGui::CollapsingHeader("TileMap"))
					{

					}
					break;


				default:
					break;
				}
			}

			ImGui::Separator();

			const char* comps[] = { "UI", "Script", "Physics" };

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

					}
				ImGui::EndPopup();
			}
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
			std::string result;
			if (ifd::FileDialog::Instance().GetResult().u8string().find_last_of('\\') != std::string::npos)
			{
				result = ifd::FileDialog::Instance().GetResult().u8string().find_last_of('\\');
				
				if (ifd::FileDialog::Instance().HasResult() && result != path)
				{
					c->SetTexture(AssetManager::GetInstance()->LoadTexture(result, ifd::FileDialog::Instance().GetResult().u8string()));
				}
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

		c->SetMass(physMass);
		c->SetGravity(physGrav);
		c->SetFriction(physFric);
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
				c->AddScript(ifd::FileDialog::Instance().GetResult().u8string());
			}
			ifd::FileDialog::Instance().Close();
		}

		ImGui::PopID();
	}

	InspectorWidget::InspectorWidget()
	{
	}
	InspectorWidget::~InspectorWidget()
	{
	}
}