#pragma once

#include "Engine/Renderer/Context.h"

#include <Windows.h>

#pragma comment(lib, "OpenGL32.lib") // Assuming the user has microsoft SDK. F for linux users

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "OpenGL/imgui_impl_opengl3.h"

#include <Glad/glad.h>

#include <Common.h>
#include "Sprite.h"
#include <time.h>

namespace Engine
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen);

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void SwapBuffers() override;

		virtual int GetCardMemory() override { return mMemorySize; }
		virtual std::string GetCardName() override { return mName; }

	private:
		unsigned int mMemorySize;
		std::string mName;

		unsigned int mVAO;

		UINT32 mScreenWidth;
		UINT32 mScreenHeight;

		HWND mHWND;

		HDC deviceContext;
		HGLRC renderContext;

		GLuint mRequiredVAO;

		TileMap testMap;
		std::vector<Sprite*> ThingsToRender;
		Sprite* mTempSprite;
	};
}

