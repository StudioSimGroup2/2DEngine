#include "InputManager.h"



namespace Engine
{
	InputManager* InputManager::mInstance = nullptr;
	
	InputManager* InputManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new InputManager();

		return mInstance;
	}

	void InputManager::ProcessInput(uint32_t key)
	{
		for (std::function<void()>& callback : mInputCallback[key])
		{
			callback();
		}
	}

	void InputManager::BindCommandToButton(uint32_t key, const std::function<void()>& callback)
	{
		mInputCallback[key].push_back(callback);
	}
}
