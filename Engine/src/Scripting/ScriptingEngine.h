#pragma once

#define SOL_ALL_SAFETIES_ON 1
#pragma warning (disable : 4251)

#include <Engine/Core.h>

#include <sol.hpp>

namespace Engine
{
	class GameObject;

	class ENGINE_API ScriptingEngine
	{
	public:
		void Init();

		static void Shutdown();

		static ScriptingEngine* GetInstance();

		sol::state& GetState() { return mState; }

	private:
		void RegisterUserTypes();

		ScriptingEngine() {}

		static ScriptingEngine* mInstance;

		sol::environment mGlobalEnvironment;

		sol::state mState;;
	};
}