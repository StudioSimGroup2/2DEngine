#include "ScriptingEngine.h"
#include <SceneManager.h>
#include <Entities/GameObject.h>
#include <Utils/AssetManager.h>

#include <string>

#include <lua.hpp>

namespace Engine
{
	ScriptingEngine* ScriptingEngine::mInstance = nullptr;
	
	void ScriptingEngine::Init()
	{
		mState.open_libraries(sol::lib::base);
		mGlobalEnvironment = sol::environment(mState, sol::create, mState.globals());

		RegisterUserTypes();

		mState.set_function("OnKeyDown", [](uint32_t key) { return InputManager::GetInstance()->GetKeyDown(key); });
		mState.set_function("OnKeyUp", [](uint32_t key) { return InputManager::GetInstance()->GetKeyUp(key); });
		mState.set_function("ChangeScene", [](std::string Path) { return SceneManager::GetInstance()->LoadScene(Path); });
		mState.set_function("CheckTrigger", [](std::string Obj1, std::string Obj2) { return Collision::CheckTrigger(SceneManager::GetInstance()->GetSceneObjectByName(Obj1), SceneManager::GetInstance()->GetSceneObjectByName(Obj2));});
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

	void ScriptingEngine::RegisterUserTypes()
	{
		mState.new_usertype<vec2f>("vec2f",
			sol::constructors<
			vec2f(),
			vec2f(float, float),
			vec2f(vec2f&)
			>(),

			"x", &vec2f::x,
			"y", &vec2f::y);

		mState.new_usertype<GameObject>("GameObject",
			"SetName", &GameObject::SetName,
			"GetName", &GameObject::GetName,

			"SetParent", &GameObject::Attach, // this might not work
			"GetParent", &GameObject::GetParent,

			"IsActive", &GameObject::IsEnabled,
			"Enable", &GameObject::EnableObject,
			"Disable", &GameObject::DisableObject,

			"MakeSprite", [](GameObject& go) { return go.AddComponent<SpriteComp>(new SpriteComp); },

			"GetTransform", &GameObject::GetComponent<TransformComp>,
			"GetSprite", &GameObject::GetComponent<SpriteComp>,
			"GetPhysics", &GameObject::GetComponent<PhysicsComp>
			);

		mState.new_usertype<Component>("Component",
			"GetOwner", &Component::GetGameObject,
			"GetType", &Component::GetType
			);

		mState.new_usertype<TransformComp>("TransformComp",
			sol::base_classes, sol::bases<Component>(),

			"SetPosition", &TransformComp::SetPosition,
			"GetPosition", &TransformComp::GetPosition,

			"SetRotation", &TransformComp::SetRotation,
			"GetRotation", &TransformComp::GetRotation,

			"SetScale", &TransformComp::SetScale,
			"GetScale", &TransformComp::GetScale
			);

		mState.new_usertype<SpriteComp>("SpriteComp", 
			sol::base_classes, sol::bases<Component>(),

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

		/*mState.new_usertype<CameraComp>("CameraComp",
		sol::base_classes, sol::bases<Component>(),

		);*/

		/*mState.new_usertype<TileMapComp>("TileMapComp",
		sol::base_classes, sol::bases<Component>(),

		);*/

		mState.new_usertype<PhysicsComp>("PhysicsComp",
			sol::base_classes, sol::bases<Component>(),

			"AddThrust", &PhysicsComp::AddThrust,

			"GetMass", &PhysicsComp::GetMass,
			"GetGravity", &PhysicsComp::GetGravity,
			"GetFriction", &PhysicsComp::GetFriction,
			"GetMaxSpeed", &PhysicsComp::GetMaxSpeed,
			"GetVelocity", &PhysicsComp::GetVelocity,
			"GetGrounded", &PhysicsComp::GetGrounded,

			"SetMass", &PhysicsComp::SetMass,
			"SetGravity", &PhysicsComp::SetGravity,
			"SetFriction", &PhysicsComp::SetFriction,
			"SetMaxSpeed", &PhysicsComp::SetMaxSpeed,
			"SetGrounded", &PhysicsComp::SetGrounded
		);

		
	}
}