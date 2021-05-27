#pragma once

#include <map>
#include <functional>
#include <Utils/Math.h>
#include <cstring>

#include "Engine/Core.h"

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

#pragma region KeyCodes
#define		MOUSE_LB	01
#define		MOUSE_RB	02
#define		MOUSE_MB	04
#define		MOUSE_FB	05
#define		MOUSE_BB	06

#define		KEY_L_SHIFT 340
#define		KEY_R_SHIFT 344
#define		KEY_SPACE	32
#define		KEY_L_ALT	342
#define		KEY_R_ALT	346

#define 	KEY_A		65
#define 	KEY_B		66
#define 	KEY_C		67
#define 	KEY_D		68
#define 	KEY_E		69
#define 	KEY_F		70
#define 	KEY_G		71
#define 	KEY_H		72
#define 	KEY_I		73
#define 	KEY_J		74
#define 	KEY_K		75
#define 	KEY_L		76
#define 	KEY_M		77
#define 	KEY_N		78
#define 	KEY_O		79
#define 	KEY_P		80
#define 	KEY_Q		81
#define 	KEY_R		82
#define 	KEY_S		83
#define 	KEY_T		84
#define 	KEY_U		85
#define 	KEY_V		86
#define 	KEY_W		87
#define 	KEY_X		88
#define 	KEY_Y		89
#define 	KEY_Z		90
#pragma endregion KeyCodes

enum KB_STATE
{
	KB_NOSTATE = 0,
	KB_PRESS,
	KB_REPEAT,
	KB_RELEASE
};

enum MB_STATE
{
	MB_NOSTATE = 0,
	MB_PRESS,
	MB_REPEAT,
	MB_RELEASE
};

#define KB_MAX_COMBO 4;

namespace Engine
{
	class ENGINE_API InputManager
	{
	public:
		static InputManager* GetInstance();

		void KeyPress(uint32_t key);
		void KeyRelease(uint32_t key);

		void ProcessKeyboard();
		void ProcessMouse();

		void BindCommandToButton(uint32_t key, const std::function<void()>& callback);

		vec2f SetMousePosition(const vec2f& mousePos) { return mMousePos = mousePos; }
		vec2f GetMousePosition() const { return mMousePos; }

		void SetMouseScreenPosition(const vec2f& mousePos) {  mMouseScreenPos = mousePos; }
		vec2f GetMouseScreenPosition() const { return mMouseScreenPos; }

		void SetScreenSize(vec2f Window, vec2f RenderTarget) { mScreenSize.x = RenderTarget.x / Window.x;
																 mScreenSize.y = RenderTarget.y / Window.y;}
		vec2f GetScreenSize()const { return mScreenSize; }


		bool GetKeyDown(uint32_t key);
		bool GetKeyRepeat(uint32_t key);
		bool GetKeyUp(uint32_t key);

		static void Shutdown();

	private:
		InputManager();

		void HandleCallbacks(uint32_t key);

		std::map<uint32_t, std::vector<std::function<void()>>> mInputCallback;

		static InputManager* mInstance;

		KB_STATE* mKeyboard;
		bool* mKBPressed;
		bool* mKBPressedPrev;

		MB_STATE* mMouse;
		bool* mMBPressed;
		bool* mMBPressedPrev;

		vec2f mMousePos;
		vec2f mMouseScreenPos;

		vec2f mScreenSize = vec2f(1, 1);
		int mScrollWheel;
	};
}

