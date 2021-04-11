#include "Application.h"
#include "Utils/AssetManager.h"
#include "Audio/AudioManager.h"

namespace Engine
{
	Application* Application::mInstance = nullptr;

	Application::Application()
	{
		if (mInstance != nullptr)
		{
			return;
		}

		mInstance = this;

		Logger::Init(GetStdHandle(STD_OUTPUT_HANDLE)); // Get handel to console (for text coloring)
		Logger::SetLogLevel(LogStates::LOG_ERR | LogStates::LOG_WARN | LogStates::LOG_MSG);

		Logger::LogMsg("Logger initalised!", __FILE__);

		mWindow = std::unique_ptr<Window>(Window::Create());

		mLayerStack = new LayerStack();

		mGUILayer = new GUILayer();
		AddLayer(mGUILayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (mRunning)
		{
			for (Layer* l : *mLayerStack)
			{
				l->Update();
			}

			InputManager::GetInstance()->ProcessMouse();
			InputManager::GetInstance()->ProcessKeyboard();

			mWindow->OnUpdate();
		}
	}

	void Application::ForceShutdown()
	{
		if (!mRunning)
		{
			return;
		}
		
		mRunning = false;

		if (mLayerStack)
		{
			delete mLayerStack;
			mLayerStack = nullptr;
		}

		mGUILayer = nullptr;

		AudioManager::GetInstance()->Shutdown();
		InputManager::GetInstance()->Shutdown();
		AssetManager::GetInstance()->Shutdown();

		mWindow->Shutdown();
	}

	void Application::AddLayer(Layer* layer)
	{
		mLayerStack->AddLayerToStack(layer);
	}

	void Application::RemoveLayer(Layer* layer)
	{
		mLayerStack->RemoveLayerFromStack(layer);
	}
}
