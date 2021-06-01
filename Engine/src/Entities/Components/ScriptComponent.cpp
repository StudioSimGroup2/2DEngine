#include "ScriptComponent.h"
#include "Scripting\ScriptingEngine.h"

#include "Entities/GameObject.h"

namespace Engine
{
	ScriptComp::ScriptComp()
	{
	}

	ScriptComp::~ScriptComp()
	{
		mPath.clear();

		mParent = nullptr;
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

		mScript.CallRender(mParent);
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

	void ScriptComp::InternalUpdate()
	{
	}

	void ScriptComp::InternalRender()
	{
	}
}