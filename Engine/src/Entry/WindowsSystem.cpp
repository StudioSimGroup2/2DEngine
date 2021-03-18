#include "WindowsSystem.h"

#include "imgui.h"
#include "imgui_impl_win32.h"

#include "Engine/Defines.h"
#include "Engine/Input/InputManager.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend\D3D11\D311Context.h"
#include "D3D11\imgui_impl_dx11.h"
#elif GRAPHICS_LIBRARY == 1
#include "Backend\OGL\OpenGLContext.h"
#include "OpenGL\imgui_impl_opengl3.h"
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // Extern from IMGUI (used to get input data)

void HelloWorld()
{
	std::cout << "Hello";
}

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

		while (WM_QUIT != msg.message)
		{
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
				mRenderer->OnUpdate(mFrameTime.count());
				mRenderer->SwapBuffers();
			}

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
		ImGui_ImplWin32_Shutdown();

#if GRAPHICS_LIBRARY == 1
		ImGui_ImplOpenGL3_Shutdown();
#else
		ImGui_ImplDX11_Shutdown();
#endif

		ImGui::DestroyContext();
		
		if (mRenderer)
		{
			delete mRenderer;
			mRenderer = nullptr;
		}

		exit(0);
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
		wndclass.hInstance = GetModuleHandle(NULL);
		wndclass.lpszClassName = L"EngineWindowClass";
		wndclass.lpszMenuName = L"";
		wndclass.style = CS_OWNDC;
		wndclass.lpfnWndProc = &WndProc;

		// TODO: Error checking
		RegisterClassEx(&wndclass);

		mHWND = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"EngineWindowClass", L"Sleepy Engine", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, wndclass.hInstance, this);

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
		
		case WM_KEYDOWN:
		{
			InputManager::GetInstance()->ProcessInput(wParam);
		}
		break;
		case WM_KEYUP:
		{
			
		}
		break;

		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			::PostQuitMessage(0);
			window->Shutdown();
		break;
		}

		default:
			return ::DefWindowProc(hwnd, uMSG, wParam, lParam);
		}

		return NULL;
	}
}