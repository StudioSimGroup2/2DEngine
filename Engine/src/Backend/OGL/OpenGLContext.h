#pragma once

#include "Engine/Renderer/Context.h"

#include <Windows.h>

#pragma comment(lib, "OpenGL32.lib") // Assuming the user has microsoft SDK. F for linux users

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace Engine
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen);

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void Render() override;

		virtual int GetCardMemory() override { return mMemorySize; }
		virtual std::string GetCardName() override { return mName; }

	private:
		unsigned int mMemorySize;
		std::string mName;

		UINT32 mScreenWidth;
		UINT32 mScreenHeight;

		HWND mHWND;

		HDC deviceContext;
		HGLRC renderContext;

	};
}

