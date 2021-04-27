#include "ScriptingEngine.h"
#include <SceneManager.h>
#include <Entities/GameObject.h>
#include <Utils/AssetManager.h>

#define SOL_ALL_SAFETIES_ON 1

#include <lua.hpp>
#include <sol.hpp>

struct Test
{
	int value = 300;

	void SetVal(int h)
	{
		value = h;
	}
};

namespace Engine
{
	ScriptingEngine* ScriptingEngine::mInstance = nullptr;
	
	void ScriptingEngine::Init()
	{
		sol::state lua;
		lua.open_libraries(sol::lib::base);

		GameObject* gameObject = SceneManager::GetInstance()->CreateObject();

		lua["this"] = gameObject;

		lua.new_usertype<GameObject>("GameObject",
			"SetName", &GameObject::SetName,
			"TransformComp", &GameObject::GetComponent<TransformComp>,
			"SpriteComp", &GameObject::GetComponent<SpriteComp>);

		lua.new_usertype<vec2f>("vec2f",
			sol::call_constructor, sol::factories([](float x, float y) {return vec2f(x, y); }),
			"x", &vec2f::x,
			"y", &vec2f::y);

		lua.new_usertype<TransformComp>("TransformComp",
			"x", &TransformComp::SetX,
			"y", &TransformComp::SetY,
			"GetPos", &TransformComp::GetPosition,
			"SetPos", &TransformComp::SetPosition);

		lua.new_usertype<SpriteComp>("SpriteComp",
			sol::call_constructor, sol::factories([](GameObject* go) { return go->AddComponent<SpriteComp>(new SpriteComp); }),
			"SetTexture", &SpriteComp::SetTexturePath);

		lua.script_file("Assets/Scripts/Player.lua");
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