#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <Engine/Core.h>

#include <sol.hpp>

namespace Engine
{
	class ENGINE_API ScriptingEngine
	{
	public:
		void Init();

		static void Shutdown();

		static ScriptingEngine* GetInstance();

		void Update(); // Temporary!

	private:
		void RegisterUserTypes();

		ScriptingEngine() {}

		static ScriptingEngine* mInstance;

		sol::state state;

		sol::protected_function mfunc;
	};
}