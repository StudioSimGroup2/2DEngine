#include "Script.h"

#include "Scripting\ScriptingEngine.h"

#include "Entities\GameObject.h"

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
		ScriptingEngine::GetInstance()->GetState().safe_script_file(mPath);

		mStart = ScriptingEngine::GetInstance()->GetState()["OnStart"];
		mUpdate = ScriptingEngine::GetInstance()->GetState()["OnUpdate"];
		mRender = ScriptingEngine::GetInstance()->GetState()["OnRender"];
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
