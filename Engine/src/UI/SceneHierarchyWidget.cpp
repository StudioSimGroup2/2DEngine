#include "SceneHierarchyWidget.h"

#include "imgui.h"

#include "SceneManager.h"


namespace Engine
{
	GameObject* SceneHierarchyWidget::mCurrentSelectedNode = nullptr;

	void SceneHierarchyWidget::Render()
	{
		ImGui::Begin("Scene Hierarchy");
		static int selectionMask = (1 << 2);
		int sceneIndex = 0;
		int nodeClicked = -1;

		if (!SceneManager::GetInstance()->GetSceneObjects().empty())
		{
			for (auto go : SceneManager::GetInstance()->GetSceneObjects())
			{
				if (go->GetParent() == nullptr)
					CreateNode(go, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth, sceneIndex, nodeClicked, selectionMask);
			}
		}

		if (nodeClicked != -1)
		{
			// Update selection state
			// (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
			if (ImGui::GetIO().KeyCtrl)
				selectionMask ^= (1 << nodeClicked);          // CTRL+click to toggle
			else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
				selectionMask = (1 << nodeClicked);           // Click to single-select
		}

		ImGui::End();
	}

	void SceneHierarchyWidget::CreateNode(GameObject* go, int flags, int& index, int& nodeClicked, int& selectionMask)
	{
		ImGui::PushID(index);
		ImGuiTreeNodeFlags node_flags = flags;
		const bool is_selected = (selectionMask & (1 << index)) != 0;
		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)index, node_flags, go->GetName().c_str());

		if (ImGui::IsItemClicked())
		{
			nodeClicked = index;
			mCurrentSelectedNode = go;
		}

		if (node_open)
		{
			for (GameObject* child : go->GetChildren())
			{
				index++;
				CreateNode(child, flags, index, nodeClicked, selectionMask);
			}

			ImGui::TreePop();
		}
		ImGui::PopID();
		index++;
	}
	
	SceneHierarchyWidget::SceneHierarchyWidget()
	{
	}

	SceneHierarchyWidget::~SceneHierarchyWidget()
	{
	}
}