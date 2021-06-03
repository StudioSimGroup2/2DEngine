#include "Application.h"
#include "Utils/AssetManager.h"
#include "Audio/AudioManager.h"

#include "Input/InputManager.h"
#include "Memory/MemoryManager.h"
#include <SceneManager.h>

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

		//MemoryManager::GetInstance();

		mWindow = std::unique_ptr<Window>(Window::Create());

		mLayerStack = new LayerStack();

		mGUILayer = new GUILayer();
		AddLayer(mGUILayer);

		SceneManager::GetInstance()->CreateScene();
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

		AudioManager::Shutdown();
		InputManager::Shutdown();
		AssetManager::Shutdown();

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
