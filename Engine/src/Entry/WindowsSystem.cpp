#include "WindowsSystem.h"

#include "Engine/Defines.h"
#include "Engine/Input/InputManager.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend\D3D11\D311Context.h"
#elif GRAPHICS_LIBRARY == 1
#include "Backend\OGL\OpenGLContext.h"
#endif

#include <windowsx.h>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <iostream>

#include <Engine/Application.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam);

namespace Engine
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam);

	Window* Window::Create(const WindowData& data)
	{
		return new WindowsSystem(data);
	}

	WindowsSystem::WindowsSystem(const WindowData& data)
	{
		mTitle = data.mTitle;
		mWidth = data.mWidth;
		mHeight = data.mHeight;

		EnableVSync(true);
		EnableFullScreen(false);

		Init(data);
	}

	WindowsSystem::~WindowsSystem()
	{
		Shutdown();
	}

	void WindowsSystem::OnUpdate()
	{
		MSG msg = {};

		mCurrentTime = std::chrono::high_resolution_clock::now();

		mNewTime = std::chrono::high_resolution_clock::now();
		mFrameTime = mNewTime - mCurrentTime;
		mCurrentTime = mNewTime;

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (mRenderer)
		{
			mRenderer->OnUpdate(static_cast<float>(mFrameTime.count()));  //everything is updating too fast, we need to cap the update speed
			mRenderer->SwapBuffers();
		}
	}

	void WindowsSystem::EnableVSync(bool option)
	{
	}

	void WindowsSystem::EnableFullScreen(bool option)
	{
	}

	void WindowsSystem::Shutdown()
	{
		if (mRenderer)
		{
			delete mRenderer;
			mRenderer = nullptr;
		}

		DestroyWindow(mHWND);
		UnregisterClass(mClassName, mHInstance);
	}

	void WindowsSystem::Init(const WindowData& data)
	{
		WNDCLASSEX wndclass;
		ZeroMemory(&wndclass, sizeof(WNDCLASSEX));
		wndclass.cbClsExtra = NULL;
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.cbWndExtra = NULL;
		wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		mHInstance = GetModuleHandle(NULL);
		wndclass.hInstance = mHInstance;
		wndclass.lpszClassName = mClassName;
		wndclass.lpszMenuName = L"";
		wndclass.style = CS_OWNDC;
		wndclass.lpfnWndProc = &WndProc;

		// TODO: Error checking
		RegisterClassEx(&wndclass);

		mHWND = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, mClassName, L"Sleepy Engine", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, mHInstance, this);

#if GRAPHICS_LIBRARY == 1
		mRenderer = new OpenGLContext(mHWND, mWidth, mHeight, true, false);
#else
		mRenderer = new D311Context(mHWND, mWidth, mHeight, true, false);
#endif
		ShowWindow(mHWND, SW_SHOW);
		UpdateWindow(mHWND);

		InputManager::GetInstance();

		mRenderer->Init();
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam)
	{	
		if (shuttingDown)
			return NULL;
		
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMSG, wParam, lParam))
			return true;

		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		switch (uMSG)
		{
		case WM_CREATE:
		{
			window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			break;
		}

		case WM_MOUSEMOVE:
		{
			InputManager::GetInstance()->SetMousePosition(vec2f((float)LOWORD(lParam), (float)HIWORD(lParam)));
		}
		break;

		case WM_KEYDOWN:
		{
			InputManager::GetInstance()->KeyPress(static_cast<uint32_t>(wParam));
		}
		break;

		case WM_KEYUP:
		{
			InputManager::GetInstance()->KeyRelease(static_cast<uint32_t>(wParam));
		}
		break;

		case WM_LBUTTONDOWN:
		{
			InputManager::GetInstance()->KeyPress(MOUSE_LB);
		}
		break;

		case WM_LBUTTONUP:
		{
			InputManager::GetInstance()->KeyRelease(MOUSE_LB);
		}
		break;

		case WM_MBUTTONDOWN:
		{
			InputManager::GetInstance()->KeyPress(MOUSE_MB);
		}
		break;

		case WM_MBUTTONUP:
		{
			InputManager::GetInstance()->KeyRelease(MOUSE_MB);
		}
		break;

		case WM_RBUTTONDOWN:
		{
			InputManager::GetInstance()->KeyPress(MOUSE_RB);
		}
		break;

		case WM_RBUTTONUP:
		{
			InputManager::GetInstance()->KeyRelease(MOUSE_RB);
		}
		break;

		case WM_XBUTTONDOWN:
		{
			if (wParam == 65568)
				InputManager::GetInstance()->KeyPress(MOUSE_BB);
			else
				InputManager::GetInstance()->KeyPress(MOUSE_FB);
		}
		break;

		case WM_XBUTTONUP:
		{
			if (wParam == 65536)
				InputManager::GetInstance()->KeyRelease(MOUSE_BB);
			else
				InputManager::GetInstance()->KeyRelease(MOUSE_FB);
		}
		break;

		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			shuttingDown = true;
			Application::GetInstance()->ForceShutdown();
			PostQuitMessage(0);
			
			break;
		}

		default:
			return ::DefWindowProc(hwnd, uMSG, wParam, lParam);
		}

		return NULL;
	}
}