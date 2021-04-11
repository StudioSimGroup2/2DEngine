#pragma once
#include <Engine/Layer.h>

#include <Entities/GameObject.h>

// This is the editor interface

using namespace Engine;

class GUILayer : public Engine::Layer
{
public:
	GUILayer();
	~GUILayer() override;

	void Render() override;
	void Update() override;

private:
	GameObject* mCurrentSelectedNode = nullptr;

	void SpriteComponent(SpriteComp* c);
	void TransformComponent(TransformComp* c);
	void CreateNode(GameObject* go, int flags, int& index, int& nodeClicked, int& selectionMask);
};

