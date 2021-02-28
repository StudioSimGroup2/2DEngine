//===================================
// Code based off Handes-On C++ Game Animation Programming - Gabor Szauer
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
#include <LevelMap.h>
#include "OGLRenderer2D.h"

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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Setup ImGUI

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); // Currently dont need IO so commented out...
		ImGui_ImplWin32_Init(mHWND);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();

		AssetManager::GetInstance()->LoadShader(nullptr, std::string("Default"), std::string("default.glsl"));

		testMap = LevelMap::LoadLevelMap((char*)"TileMaps/FirstTest.txt");

		return; // Texture loading needs to be implemented !!!!!

		for (int X = 0; X < testMap.size(); X++)
		{
			for (int Y = 0; Y < testMap[0].size(); Y++)
			{
				switch (testMap[X][Y])
				{
				case 0:
				{

					break;
				}
				case 1:
				{
					Sprite* mapItem = new Sprite(nullptr, std::string("Tile ") + std::string(X + "" + Y) + std::string("]"),
						std::string("Textures/stone.dds"), vec2f(32.0f * Y, 32.0f * X)); // someone got their x and y coords wrong, i'll fix it later
					OGLRenderer2D* re = new OGLRenderer2D(static_cast<OGLShader*>(AssetManager::GetInstance()->GetShaderByName("Default")));
					mapItem->AddRendererComponent(re);

					ThingsToRender.push_back(mapItem);
					break;
				}
				default:
					break;
				}
			}
		}

		mTempSprite = new Sprite(nullptr, std::string("Mario"), std::string("Textures/Mario.png"), vec2f(32.0f));
		OGLRenderer2D* renderer = new OGLRenderer2D(static_cast<OGLShader*>(AssetManager::GetInstance()->GetShaderByName("Default")));
		mTempSprite->AddRendererComponent(renderer);
	}

	void OpenGLContext::Shutdown()
	{

	}

	void OpenGLContext::OnUpdate(float deltaTime)
	{
	}

	void OpenGLContext::Render()
	{
		//glClearColor(0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto Thing : ThingsToRender)
			Thing->Draw();

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