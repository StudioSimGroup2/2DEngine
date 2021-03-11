#include "Application.h"

namespace Engine
{
	Application::Application()
	{
		mWindow = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
		mWindow->Shutdown();
	}

	void Application::Run()
	{
		while (mRunning)
		{
			mWindow->OnUpdate();
		}
	}
}
