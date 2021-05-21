#pragma once

namespace Engine
{
	class GameObject;
	
	class SceneHierarchyWidget
	{
	public:
		SceneHierarchyWidget();
		~SceneHierarchyWidget();

		void Render();

		static GameObject* GetNode() { return mCurrentSelectedNode; }
		static void ClearNode() { mCurrentSelectedNode = nullptr; }

	private:
		void CreateNode(GameObject* go, int flags, int& index, int& nodeClicked, int& selectionMask);

		static GameObject* mCurrentSelectedNode;
	};

}