#include "MenuBarWidget.h"

#include "imgui.h"
#include "ImFileDialog\ImFileDialog.h"

#include "SceneManager.h"
#include "GUILayer.h"

namespace Engine
{
	void MenuBarWidget::Render()
	{
		float menuBar;

		// Menu
		if (ImGui::BeginMainMenuBar())
		{
			menuBar = ImGui::GetWindowSize().y;
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Project CTRL + N")) {
					// No Impl
				}
				if (ImGui::MenuItem("Open Project CTRL + O"))
				{
					ifd::FileDialog::Instance().Open("File Browser", "Open a Project", "Engine Project File (*.prj){.prj},.*");
				}
				if (ImGui::MenuItem("Save Project CTRL + S"))
				{
					//ifd::FileDialog::Instance().Open("File Browser", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
				}
				if (ImGui::MenuItem("Save Project As CTRL + SHIFT + S"))
				{

				}
				if (ImGui::MenuItem("Recent Projects"))
				{

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Import Project"))
				{

				}
				if (ImGui::MenuItem("Export Project"))
				{

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Preferences"))
				{

				}
				ImGui::EndMenu();
			}

			//ImGui::ShowDemoWindow();
			if (ImGui::BeginMenu("Scene"))
			{			
				//Load Scene
				//----------------------------------------------------------------------------------------------
				if (ImGui::Button("Load scene"))
				{
					ifd::FileDialog::Instance().Open("SceneLoader", "Load", "Load (*.xml){.xml},.*");
				}
				if (ifd::FileDialog::Instance().IsDone("SceneLoader"))
				{
					if (ifd::FileDialog::Instance().HasResult())
					{
						std::string TempString = ifd::FileDialog::Instance().GetResult().u8string();
						SceneManager::GetInstance()->LoadScene(TempString);
					}
					ifd::FileDialog::Instance().Close();
				}
				//----------------------------------------------------------------------------------------------
				
				//Save Scene
				//----------------------------------------------------------------------------------------------
				if (ImGui::Button("Save scene"))
				{
					ifd::FileDialog::Instance().Save("SceneSaver", "Save", "Save (*.xml){.xml},.*");
				}
				if (ifd::FileDialog::Instance().IsDone("SceneSaver"))
				{
					if (ifd::FileDialog::Instance().HasResult())
					{
						std::string TempString = ifd::FileDialog::Instance().GetResult().u8string();
						SceneManager::GetInstance()->SaveScene(TempString);
					}
					ifd::FileDialog::Instance().Close();
				}
				//----------------------------------------------------------------------------------------------

				//Clear Scene
				//----------------------------------------------------------------------------------------------
				if (ImGui::MenuItem("Clear scene"))
				{
					SceneManager::GetInstance()->ClearScene();
				}
				//----------------------------------------------------------------------------------------------

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Empy Game Object"))
				{
					SceneManager::GetInstance()->CreateObject();
				}

				if (ImGui::MenuItem("Empty Child GameObject"))
				{
					if (SceneHierarchyWidget::GetNode() != nullptr)
					{
						SceneManager::GetInstance()->CreateObject()->Attach(SceneHierarchyWidget::GetNode());
					}
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Sprite"))
				{
					if (SceneHierarchyWidget::GetNode() == nullptr)
					{
						SceneManager::GetInstance()->CreateObject()->AddComponent<SpriteComp>(new SpriteComp);
					}
					else
					{
						auto go =  SceneManager::GetInstance()->CreateObject();
						go->AddComponent<SpriteComp>(new SpriteComp);
						go->Attach(SceneHierarchyWidget::GetNode());
					}
				}

				if (ImGui::MenuItem("TileMap"))
				{
					if (SceneHierarchyWidget::GetNode() == nullptr)
					{
						SceneManager::GetInstance()->CreateObject()->AddComponent<TileMapComp>(new TileMapComp);
					}
					else
					{
						auto go = SceneManager::GetInstance()->CreateObject();
						go->AddComponent<TileMapComp>(new TileMapComp);
						go->Attach(SceneHierarchyWidget::GetNode());
					}
				}

				if (ImGui::MenuItem("Camera"))
				{
					if (SceneHierarchyWidget::GetNode() == nullptr)
					{
						SceneManager::GetInstance()->CreateObject()->AddComponent<CameraComp>(new CameraComp);
					}
					else
					{
						auto go = SceneManager::GetInstance()->CreateObject();
						go->AddComponent<CameraComp>(new CameraComp);
						go->Attach(SceneHierarchyWidget::GetNode());
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo CTRL + Z"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Redo CTRL + Y"))
				{
					// No Impl
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Build"))
			{
				if (ImGui::MenuItem("Run"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Debug"))
				{
					// No Impl
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Asset Manager"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Console"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Inspector"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Scene Hierarchy"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Audio Manager"))
				{
					// No Impl
				}
				if (ImGui::MenuItem("Profiler"))
				{
					// No Impl
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About"))
				{
					// No Impl
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	MenuBarWidget::MenuBarWidget()
	{
	}

	MenuBarWidget::~MenuBarWidget()
	{
	}
}