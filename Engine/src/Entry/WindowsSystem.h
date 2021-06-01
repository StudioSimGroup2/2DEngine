#pragma once

#include "../Engine/Window.h"
#include "../Engine/Renderer/Context.h"
#include "EngineTime.h"

#include <Windows.h>
#include <chrono>

static bool shuttingDown = false;

namespace Engine
{
	class WindowsSystem : public Window
	{
	public:
		WindowsSystem(const WindowData& data);
		virtual ~WindowsSystem();

		void OnUpdate() override;
		void EnableVSync(bool option) override;
		void EnableFullScreen(bool option) override;
		void Shutdown() override;

		inline unsigned int GetWidth() const override { return mWidth; }
		inline unsigned int GetHeight() const override { return mHeight; }

		HWND GetHWND() { return mHWND; }

	private:
		virtual void Init(const WindowData& data);

		// TODO: Window Events

		std::string mTitle;
		unsigned int mWidth;
		unsigned int mHeight;

		HWND mHWND;

		Context* mRenderer;

		LPCWSTR mClassName = L"abc";
		HINSTANCE mHInstance{};

		// DeltaTime calculations
		std::chrono::time_point<std::chrono::high_resolution_clock> mCurrentTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> mNewTime;
		std::chrono::duration<double> mFrameTime;	// Frame time is measured in millseconds
	};
}

