//===================================
// Code based off Hands-On C++ Game Animation Programming - Gabor Szauer
// (c) 2020 Packt Publishing
// https://store.tutorialspoint.com/1212/9781800207967.pdf
//===============================

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include "OpenGLContext.h"

#include <iostream>
#include "Engine/Application.h"
#include <Utils/AssetManager.h>
#include <Backend/OGL/OpenGLCamera.h>
#include <CameraManager.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);

void CallToSwapBuffers(HDC device)
{
	SwapBuffers(device);
}

namespace Engine
{
	// TODO: vSync and full screen implementation
	OpenGLContext::OpenGLContext(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen)
	{
		mHWND = hwnd;
		mScreenHeight = screenHeight;
		mScreenWidth = screenWidth;
	}

	void OpenGLContext::Init()
	{
		mDeviceContext = GetDC(mHWND);

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

		int pixel = ChoosePixelFormat(mDeviceContext, &pixelFormatDesc);
		SetPixelFormat(mDeviceContext, pixel, &pixelFormatDesc);

		HGLRC tempRC = wglCreateContext(mDeviceContext);
		wglMakeCurrent(mDeviceContext, tempRC);
		auto wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		const int attribList[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_FLAGS_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		mRenderContext = wglCreateContextAttribsARB(mDeviceContext, nullptr, attribList);
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(tempRC);
		wglMakeCurrent(mDeviceContext, mRenderContext);

		if (!gladLoadGL())
		{
			std::cout << "NO! \n";
		}

		std::string card = std::string((char*)glGetString(GL_RENDERER));
		GLint memory = 0;
		glGetIntegerv(0x9048, &memory);

		DeviceData data = DeviceData(card, memory / 1024); // 8192

		OGLDevice::GetInstance()->SetDeviceData(data);
		
		RECT rc;
		GetClientRect(mHWND, &rc);
		GLsizei width = static_cast<GLsizei>(rc.right - rc.left);
		GLsizei height = static_cast<GLsizei>(rc.bottom - rc.top);

		glViewport(0, 0, width, height);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenVertexArrays(1, &mRequiredVAO);
		glBindVertexArray(mRequiredVAO);

		OGLDevice::GetInstance()->SetHGLRC(mRenderContext);

		AssetManager::GetInstance()->LoadShader("Default", "default.glsl");

		CameraManager::Get()->Add(new Camera(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
		CameraManager::Get()->Add(new Camera(glm::vec4(-964.0f, 94.0f, -1.0f, 1.0f)));
		CameraManager::Get()->GetCameraByIndex(1)->SetStatic(true);

		InputManager::GetInstance()->BindCommandToButton(KEY_Q, &CameraManager::Get()->CBCycleNext);
		InputManager::GetInstance()->BindCommandToButton(KEY_E, &CameraManager::Get()->CBCyclePrevious);
	}

	void OpenGLContext::Shutdown()
	{
	}

	void OpenGLContext::OnUpdate(float deltaTime)
	{
		CameraManager::Get()->Update(deltaTime); // Belongs in core scene update loop
	}

	void OpenGLContext::SwapBuffers()
	{
		glClearColor(0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f);
		//glClearColor(0.0f, 0.4f, 0.4f, 1.000000000f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer* l : *Application::GetInstance()->GetStack())
		{
			l->Render();
		}

		CallToSwapBuffers(mDeviceContext);
	}
}