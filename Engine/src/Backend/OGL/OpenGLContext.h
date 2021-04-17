#pragma once

#include <Windows.h>
#include <Glad/glad.h>

#pragma comment(lib, "OpenGL32.lib")

#include "Engine/Renderer/Context.h"

namespace Engine
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen);
		~OpenGLContext();

		void Init() override;
		void Shutdown() override;
		void OnUpdate(float deltaTime) override;
		void SwapBuffers() override;

	private:

		UINT32 mScreenWidth;
		UINT32 mScreenHeight;

		HWND mHWND;
		HDC mDeviceContext;
		HGLRC mRenderContext;

		GLuint mRequiredVAO;

		bool mEnableEditor = true; // Very curde, will set up an ImGUi properties struct later - Joe
		bool mShowLoggingConsole = true;
	};
}

