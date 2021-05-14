#include "ScriptingEngine.h"
#include <SceneManager.h>
#include <Entities/GameObject.h>
#include <Utils/AssetManager.h>

#include <lua.hpp>

namespace Engine
{
	ScriptingEngine* ScriptingEngine::mInstance = nullptr;
	
	void ScriptingEngine::Init()
	{
		state.open_libraries(sol::lib::base);

		RegisterUserTypes();

		GameObject* gameObject = SceneManager::GetInstance()->CreateObject();

		state["self"] = gameObject;

		state.script_file("Assets/Scripts/Player.lua");

		mfunc = state["OnUpdate"];

		state.set_function("OnKeyDown", [](uint32_t key) { return InputManager::GetInstance()->GetKeyDown(key); });
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

	void ScriptingEngine::Update()
	{
		mfunc();
	}

	void ScriptingEngine::RegisterUserTypes()
	{
		state.new_usertype<vec2f>("vec2f",
			sol::constructors<
			vec2f(),
			vec2f(float, float)
			>(),

			"x", &vec2f::x,
			"y", &vec2f::y);

		state.new_usertype<Component>("Component",
			"GetOwner", &Component::GetGameObject,
			"GetType", &Component::GetType
			);

		state.new_usertype<TransformComp>("TransformComp",
			sol::base_classes, sol::bases<Component>(),

			"SetPosition", &TransformComp::SetPosition,
			"GetPosition", &TransformComp::GetPosition,

			"SetRotation", &TransformComp::SetRotation,
			"GetRotation", &TransformComp::GetRotation,

			"SetScale", &TransformComp::SetScale,
			"GetScale", &TransformComp::GetScale
			);

		state.new_usertype<SpriteComp>("SpriteComp", sol::base_classes, sol::bases<Component>(),

			"SetPath", &SpriteComp::SetTexturePath,

			"SetTexture", &SpriteComp::SetTexture,
			"GetTexture", &SpriteComp::GetTexture,

			"SetFlipX", &SpriteComp::ToggleFlipX,
			"GetFlipX", &SpriteComp::GetFlipX,

			"SetFlipY", &SpriteComp::ToggleFlipY,
			"GetFlipY", &SpriteComp::GetFlipY,

			"SetColour", &SpriteComp::SetColour,
			"GetColour", &SpriteComp::GetColour
			);

		state.new_usertype<GameObject>("GameObject",
			"SetName", &GameObject::SetName,
			"GetName", &GameObject::GetName,

			"SetParent", &GameObject::AttachToParent,
			"GetParent", &GameObject::GetParent,

			"IsActive", &GameObject::IsEnabled,
			"Enable", &GameObject::EnableObject,
			"Disable", &GameObject::DisableObject,
			
			"MakeSprite", [](GameObject& go) { return go.AddComponent<SpriteComp>(new SpriteComp); },

			"GetTransform", &GameObject::GetComponent<TransformComp>,
			"GetSprite", &GameObject::GetComponent<SpriteComp>
			);

	
	}
}