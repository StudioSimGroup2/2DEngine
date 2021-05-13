#include "InputManager.h"
#include <iostream>

namespace Engine
{
	InputManager* InputManager::mInstance = nullptr;

	InputManager* InputManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new InputManager();

		return mInstance;
	}

	void InputManager::KeyPress(uint32_t key)
	{
		if (key <= 6)
		{
			if (mMBPressed[key])
				mMBPressedPrev[key] = true;

			mMBPressed[key] = true;
		}

		else
		{
			if (mKBPressed[key])
				mKBPressedPrev[key] = true;

			mKBPressed[key] = true;
		}
	}

	void InputManager::KeyRelease(uint32_t key)
	{
		if (key <= 6)
		{
			mMBPressed[key] = false;
		}

		else
		{
			mKBPressed[key] = false;
		}

	}

	void InputManager::BindCommandToButton(uint32_t key, const std::function<void()>& callback)
	{
		mInputCallback[key].push_back(callback);
	}

	void InputManager::ProcessKeyboard()
	{
		for (uint32_t i = 0; i < 256; i++)
		{
			if (mKBPressed[i])
			{
				if (mKeyboard[i] == KB_NOSTATE)
				{
					mKeyboard[i] = KB_PRESS;

				}
				else if (mKeyboard[i] != KB_REPEAT && mKBPressedPrev[i])
				{
					mKeyboard[i] = KB_REPEAT;
				}
				HandleCallbacks(i);
			}
			else
			{
				if ((mKeyboard[i] == KB_REPEAT) || (mKeyboard[i] == KB_PRESS))
				{
					mKeyboard[i] = KB_RELEASE;
					mKBPressedPrev[i] = false;
					mKBPressed[i] = false;
				}
				else
				{
					mKeyboard[i] = KB_NOSTATE;
				}
			}
		}
	}

	void InputManager::ProcessMouse()
	{
		for (uint32_t i = 1; i < 7; i++)
		{
			if (mMBPressed[i])
			{
				if (mMouse[i] == MB_NOSTATE)
				{
					mMouse[i] = MB_PRESS;
					mMBPressedPrev[i] = true;
					HandleCallbacks(i);
				}
				else if (mMouse[i] != MB_REPEAT && mMBPressedPrev[i])
				{
					mMouse[i] = MB_REPEAT;
				}

				HandleCallbacks(i);
			}
			else
			{
				if ((mMouse[i] == MB_REPEAT) || (mMouse[i] == MB_PRESS))
				{
					mMouse[i] = MB_RELEASE;
				}
				else
				{
					mMouse[i] = MB_NOSTATE;
				}
			}
		}
	}

	bool InputManager::GetKeyDown(uint32_t key)
	{
		if (key <= 6)
		{
			if (mMouse[key] == MB_PRESS || mMouse[key] == MB_REPEAT)
			{
				return true;
			}
		}
		else
		{
			if (mKeyboard[key] != KB_NOSTATE || mMouse[key] == KB_RELEASE)
			{
				return true;
			}
		}

		return false;
	}

	bool InputManager::GetKeyRepeat(uint32_t key)
	{
		if (key <= 6)
		{
			if (mMouse[key] == MB_REPEAT)
				return true;
		}
		else
		{
			if (mKeyboard[key] == KB_REPEAT)
				return true;
		}

		return false;
	}

	bool InputManager::GetKeyUp(uint32_t key)
	{
		if (key <= 6)
		{
			if (mMouse[key] == MB_RELEASE)
				return true;
		}
		else
		{
			if (mKeyboard[key] == KB_RELEASE)
				return true;
		}

		return false;
	}

	void InputManager::Shutdown()
	{
		if (mInstance == nullptr)
			return;

		if (mInstance->mMouse)
		{
			//delete[] mInstance->mMouse; // This results in a heap corruption. 
			mInstance->mMouse = nullptr;
		}

		if (mInstance->mKeyboard)
		{
			delete[] mInstance->mKeyboard;
			mInstance->mKeyboard = nullptr;
		}

		if (mInstance->mKBPressed)
		{
			delete[] mInstance->mKBPressed;
			mInstance->mKBPressed = nullptr;
		}

		if (mInstance->mKBPressedPrev)
		{
			delete[] mInstance->mKBPressedPrev;
			mInstance->mKBPressedPrev = nullptr;
		}
		
		if (mInstance->mMBPressed)
		{
			delete[] mInstance->mMBPressed;
			mInstance->mMBPressed = nullptr;
		}

		if (mInstance->mMBPressedPrev)
		{
			delete[] mInstance->mMBPressedPrev;
			mInstance->mMBPressedPrev = nullptr;
		}
		
		delete mInstance;
		mInstance = nullptr;
	}

	InputManager::InputManager()
	{
		mKeyboard = new KB_STATE[256];
		memset(mKeyboard, KB_NOSTATE, sizeof(KB_STATE) * 256);
		mKBPressed = new bool[256];
		memset(mKBPressed, false, sizeof(bool) * 256);
		mKBPressedPrev = new bool[256];
		memset(mKBPressedPrev, false, sizeof(bool) * 256);

		mMouse = new MB_STATE[6];
		memset(mMouse, MB_NOSTATE, sizeof(MB_STATE) * 6);
		mMBPressed = new bool[6];
		memset(mMBPressed, false, sizeof(bool) * 6);
		mMBPressedPrev = new bool[6];
		memset(mMBPressedPrev, false, sizeof(bool) * 6);
	}

	void InputManager::HandleCallbacks(uint32_t key)
	{
		for (std::function<void()>& callback : mInputCallback[key])
		{
			callback();
		}
	}
}