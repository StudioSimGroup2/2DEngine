#pragma once
#include <Engine/Layer.h>

#include <Entities/GameObject.h>

// This is the editor interface

struct ImGuiViewport;

using namespace Engine;

class GUILayer : public Engine::Layer
{
public:
	GUILayer();
	~GUILayer() override;

	void Render() override;
	void Update() override;

#if GRAPHICS_LIBRARY == 1
	#ifdef _WIN64
	static void Win32_CreateWindow(ImGuiViewport* viewport);
	static void Win32_RenderWindow(ImGuiViewport* viewport, void*);
	static void Win32_SwapBuffers(ImGuiViewport* viewport, void*);
	static void Win32_DestroyWindow(ImGuiViewport* viewport);
	#endif
#endif

private:

	GameObject* mCurrentSelectedNode = nullptr;

	void SpriteComponent(SpriteComp* c);
	void TransformComponent(TransformComp* c);
	void PhysicsComponent(PhysicsComp* c);
	void ScriptComponent(ScriptComp* c);
	void CreateNode(GameObject* go, int flags, int& index, int& nodeClicked, int& selectionMask);
};


