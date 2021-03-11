#pragma once

#include <map>
#include <functional>

///
/// 
/// 
#pragma region KeyCodes
#define 	KEY_A   65
#define 	KEY_B   66
#define 	KEY_C   67
#define 	KEY_D   68
#define 	KEY_E   69
#define 	KEY_F   70
#define 	KEY_G   71
#define 	KEY_H   72
#define 	KEY_I   73
#define 	KEY_J   74
#define 	KEY_K   75
#define 	KEY_L   76
#define 	KEY_M   77
#define 	KEY_N   78
#define 	KEY_O   79
#define 	KEY_P   80
#define 	KEY_Q   81
#define 	KEY_R   82
#define 	KEY_S   83
#define 	KEY_T   84
#define 	KEY_U   85
#define 	KEY_V   86
#define 	KEY_W   87
#define 	KEY_X   88
#define 	KEY_Y   89
#define 	KEY_Z   90
#pragma endregion KeyCodes

namespace Engine
{
	class InputManager
	{
	public:
		static InputManager* GetInstance();

		void ProcessInput(uint32_t key);

		void BindCommandToButton(uint32_t key, const std::function<void()>& callback);

	private:
		InputManager() { }

		std::map<uint32_t, std::vector<std::function<void()>>> mInputCallback;

		static InputManager* mInstance;
	};
}

