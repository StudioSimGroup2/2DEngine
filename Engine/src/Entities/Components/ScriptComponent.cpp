#include "ScriptComponent.h"
#include "Scripting\ScriptingEngine.h"

#include "Entities/GameObject.h"

namespace Engine
{
	ScriptComp::ScriptComp()
	{
		Init();
	}

	ScriptComp::ScriptComp(GameObject* parent)
	{
		Init();
	}

	ScriptComp::~ScriptComp()
	{
		mPath.clear();
	}

	void ScriptComp::Update()
	{
		if (mPath.empty())
			return;

		mScript.CallUpdate(mParent);
	}

	void ScriptComp::Render()
	{
		if (mPath.empty())
			return;
	}

	void ScriptComp::AddScript(const std::string& file)
	{
		mPath = file;

		mScript.Load("name", mPath);
	}

	void ScriptComp::Init()
	{
		mType = COMPONENT_SCRIPT;
	}
}