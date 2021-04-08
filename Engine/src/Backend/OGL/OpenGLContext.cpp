//===================================
// Code based off Hands-On C++ Game Animation Programming - Gabor Szauer
// (c) 2020 Packt Publishing
// https://store.tutorialspoint.com/1212/9781800207967.pdf
//===============================

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include "OpenGLContext.h"

#include <iostream>
#include <windows.h>
#include <Utils/AssetManager.h>
#include <Engine/Audio/AudioManager.h>
#include "OGLRenderer2D.h"
#include <Engine/Input/InputManager.h>
#include <Backend/OGL/OpenGLCamera.h>
#include <CameraManager.h>
#include "Engine/Application.h"
#include "ImFileDialog/ImFileDialog.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);

typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int);
typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);

void CallToSwapBuffers(HDC device)
{
	SwapBuffers(device);
}

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

		mRenderContext = wglCreateContextAttribsARB(mDeviceContext, 0, attribList);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempRC);
		wglMakeCurrent(mDeviceContext, mRenderContext);

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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenVertexArrays(1, &mRequiredVAO);
		glBindVertexArray(mRequiredVAO);

		OGLDevice::GetInstance()->SetHGLRC(mRenderContext);

		ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void*
		{
			GLuint tex;

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			return (void*)tex;
		};

		ifd::FileDialog::Instance().DeleteTexture = [](void* tex)
		{
			GLuint texID = (GLuint)tex;
			glDeleteTextures(1, &texID);
		};

		AssetManager::GetInstance()->LoadShader("Default", "default.glsl");

		CameraManager::Get()->Add(new Camera(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
		CameraManager::Get()->Add(new Camera(glm::vec4(-964.0f, 94.0f, -1.0f, 1.0f)));
		CameraManager::Get()->GetCameraByIndex(1)->SetStatic(true);

		Camera* cam = CameraManager::Get()->GetPrimaryCamera();

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