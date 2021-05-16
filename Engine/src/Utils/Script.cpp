#include "Script.h"

#include "Scripting\ScriptingEngine.h"
#include "Entities\GameObject.h"

#include <assert.h>

namespace Engine
{
	Script::Script()
	{
	}

	Script::~Script()
	{
	}

	void Script::Load(const std::string& name, const std::string& mPath)
	{
		mEnvironment = sol::environment(ScriptingEngine::GetInstance()->GetState(), sol::create,
			ScriptingEngine::GetInstance()->GetState().globals());
		
		ScriptingEngine::GetInstance()->GetState().script_file(mPath);

		mStart = ScriptingEngine::GetInstance()->GetState()["OnStart"];
		mUpdate = ScriptingEngine::GetInstance()->GetState()["OnUpdate"];
		mRender = ScriptingEngine::GetInstance()->GetState()["OnRender"];
		
		//sol::set_environment(mEnvironment, mStart);
		///*sol::set_environment(mEnvironment, mUpdate);*/
		//sol::set_environment(mEnvironment, mRender);
	}

	void Script::CallStart(GameObject* parent)
	{
		ScriptingEngine::GetInstance()->GetState()["self"] = parent;
		
		mStart();
	}

	void Script::CallUpdate(GameObject* parent)
	{
		ScriptingEngine::GetInstance()->GetState()["self"] = parent;

		mUpdate();
	}

	void Script::CallRender(GameObject* parent)
	{
		ScriptingEngine::GetInstance()->GetState()["self"] = parent;
		
		mRender();
	}
}
