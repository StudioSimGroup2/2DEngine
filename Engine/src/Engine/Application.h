#pragma once
#include <memory>

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "Utils/Logger.h"
#include <Engine/Input/InputManager.h>
#include <UI/GUILayer.h>

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		~Application();

		static Application* GetInstance() { return mInstance; }
		bool GetRun() { return mRunning; }

		Window& GetWindowData() { return *mWindow; }
		
		void Run();
		void ForceShutdown();

		void AddLayer(Layer* layer);
		void RemoveLayer(Layer* layer);

		LayerStack* GetStack() const { return mLayerStack; }

	private:
		bool mRunning = true;

		std::unique_ptr<Window> mWindow;

		static Application* mInstance;

		LayerStack* mLayerStack;

		GUILayer* mGUILayer;
	};

	Application* CreateApplication();
}
