#pragma once

#include <string>

#include "Core.h"

namespace Engine
{
	struct WindowData
	{
		std::string mTitle;
		unsigned int mWidth, mHeight;

		WindowData(const std::string& title = "Engine", unsigned int width = 1280, unsigned int height = 720)
			: mTitle(title), mWidth(width), mHeight(height)
		{
		}
	};

	class ENGINE_API Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual void EnableVSync(bool option) = 0;
		virtual void EnableFullScreen(bool option) = 0;
		virtual void Shutdown() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		static Window* Create(const WindowData& data = WindowData());
		bool mForceShutdown;
	};
}