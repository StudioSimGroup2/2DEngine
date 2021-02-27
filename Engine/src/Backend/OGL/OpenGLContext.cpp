//===================================
// Code based off Handes-On C++ Game Animation Programming - Gabor Szauer
// (c) 2020 Packt Publishing
// https://store.tutorialspoint.com/1212/9781800207967.pdf
//===============================

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include "OpenGLContext.h"

#include <Glad/glad.h>
#include <iostream>
#include <windows.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);

typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int);
typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);

namespace Engine
{
	OpenGLContext::OpenGLContext(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen)
	{
		mHWND = hwnd;
		mScreenHeight = screenHeight;
		mScreenWidth = screenWidth;
	}

	void OpenGLContext::Init()
	{
		deviceContext = GetDC(mHWND);

		PIXELFORMATDESCRIPTOR pixelFormatDesc;
		ZeroMemory(&pixelFormatDesc, sizeof(pixelFormatDesc));
		pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDesc.nVersion = 1;
		pixelFormatDesc.dwFlags = LPD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits = 24;
		pixelFormatDesc.cDepthBits = 32;
		pixelFormatDesc.cStencilBits = 8;
		pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

		int pixel = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
		SetPixelFormat(deviceContext, pixel, &pixelFormatDesc);

		HGLRC tempRC = wglCreateContext(deviceContext);
		wglMakeCurrent(deviceContext, tempRC);
		PFNWGLCREATECONTEXTATTRIBSARBPROC
			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
			wglGetProcAddress("wglCreateContextAttribsARB");

		const int attribList[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_FLAGS_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		renderContext = wglCreateContextAttribsARB(deviceContext, 0, attribList);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempRC);
		wglMakeCurrent(deviceContext, renderContext);


		if (!gladLoadGL())
		{
			std::cout << "NO! \n";
		}

		std::cout << "OpenGL Context: " << GLVersion.major << ", " << GLVersion.minor << "\n";
		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

		RECT rc;
		GetClientRect(mHWND, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		glViewport(0, 0, width, height);

		// Setup ImGUI

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); // Currently dont need IO so commented out...
		ImGui_ImplWin32_Init(mHWND);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();
	}

	void OpenGLContext::Shutdown()
	{

	}

	void OpenGLContext::OnUpdate(float deltaTime)
	{
	}

	void OpenGLContext::Render()
	{
		glClearColor(0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Temp ImGui window!");
		ImGui::Text("Hello world!");
		ImGui::End();

		ImGui::Begin("Framerate");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SwapBuffers(deviceContext);
	}

}