#pragma once
#include "Window.h"
#include <memory>

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		bool mRunning = true;

		std::unique_ptr<Window> mWindow;


	};
}
