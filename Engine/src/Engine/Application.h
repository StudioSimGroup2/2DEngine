#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include <memory>
#include "Utils/Logger.h"

#include "GUILayer.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		~Application();

		static Application* GetInstance() { return mInstance; }
		Window& GetWindowData() { return *mWindow; }

		void Run();

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
