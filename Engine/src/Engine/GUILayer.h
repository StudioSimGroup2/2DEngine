#pragma once
#include <Engine/Layer.h>
#include <SceneManager.h>

// This is the editor interface

class GUILayer : public Engine::Layer
{
public:
	GUILayer();
	~GUILayer() override;

	void Render() override;
	void Update() override;

private:
	GameObject* mCurrentSelectedNode = nullptr;

	void CreateNode(GameObject* go, int flags, int& index, int& nodeClicked, static int& selectionMask);
};

