#pragma once

#include "../Engine/Window.h"
#include "../Engine/Renderer/Context.h"

#include <Windows.h>

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

		inline unsigned int GetWidth() const override { return mWidth; }
		inline unsigned int GetHeight() const override { return mHeight; }

	protected:
		HWND mHWND;

	private:
		virtual void Init(const WindowData& data);
		virtual void Shutdown();

		// TODO: Window Events

		std::string mTitle;
		unsigned int mWidth;
		unsigned int mHeight;

		Context* mRenderer;
	};
}

