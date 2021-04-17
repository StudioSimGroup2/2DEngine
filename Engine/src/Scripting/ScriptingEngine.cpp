#include "ScriptingEngine.h"

#define SOL_ALL_SAFETIES_ON 1

#include <lua.hpp>
#include <sol.hpp>

namespace Engine
{
	ScriptingEngine* ScriptingEngine::mInstance = nullptr;
	
	void ScriptingEngine::Init()
	{
		sol::state lua;
		lua.open_libraries(sol::lib::base);

		lua.script("print('Hello from lua')");
	}

	void ScriptingEngine::Shutdown()
	{
		if (mInstance == nullptr)
			return;
	}

	ScriptingEngine* ScriptingEngine::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new ScriptingEngine();
		}

		return mInstance;
	}
}