#pragma once

#include "Core.h"
#include "Window.h"
#include <memory>

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		bool mRunning = true;

		std::unique_ptr<Window> mWindow;
	};

	Application* CreateApplication();
}
