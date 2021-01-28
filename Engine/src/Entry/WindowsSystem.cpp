#include "WindowsSystem.h"

#include "../Backend/D3D11/D311Context.h"

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
	}

	void WindowsSystem::OnUpdate()
	{
		MSG msg = {};

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
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

	void WindowsSystem::Init(const WindowData& data)
	{
		WNDCLASSEX wndclass;
		wndclass.cbClsExtra = NULL;
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.cbWndExtra = NULL;
		wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hInstance = NULL;
		wndclass.lpszClassName = L"EngineWindowClass";
		wndclass.lpszMenuName = L"";
		wndclass.style = NULL;
		wndclass.lpfnWndProc = &WndProc;

		// TODO: Error checking
		RegisterClassEx(&wndclass);

		mHWND = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"EngineWindowClass", L"Engine App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, NULL, this);

		ShowWindow(mHWND, SW_SHOW);
		UpdateWindow(mHWND);

		mRenderer = new D311Context(mHWND, mWidth, mHeight, true, false);
		mRenderer->Init();
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam)
	{	
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		switch (uMSG)
		{
		case WM_CREATE:
		{
			window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			break;
		}

		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			::PostQuitMessage(0);
			break;
		}

		default:
			return ::DefWindowProc(hwnd, uMSG, wParam, lParam);
		}

		return NULL;
	}

	void WindowsSystem::Shutdown()
	{
	}
}


