#pragma once
#include <Engine/Layer.h>

#include <Entities/GameObject.h>
#include "MenuBarWidget.h"
#include "SceneHierarchyWidget.h"
#include "InspectorWidget.h"
#include "LoggerWidget.h"

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
	MenuBarWidget mMenuBar;
	SceneHierarchyWidget mSceneHierarchy;
	InspectorWidget mInspector;
	LoggerWidget mLogger;
};


