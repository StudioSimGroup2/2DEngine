#pragma once
#include <vector>

#include "Engine/Core.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Input/InputManager.h"
#include "Utils/AssetManager.h"
#include "Utils/Logger.h"
#include "Component.h"
#include "ComponentIncludes.h"

namespace Engine
{
	class ENGINE_API GameObject
	{
	public:
		GameObject() { std::cout << "Gaze into the the abyss:	       " << this << std::endl; };
		GameObject(GameObject* parent) { mParent = parent; parent->AttachToParent(this); }
		~GameObject() = default;

		void Start();
		void Update();
		void FixedUpdate();
		void Render();
		void OnEnable();
		void OnDisable();

		void EnableObject() { mStatus = true; }
		void DisableObject() { mStatus = false; }
		bool IsEnabled() { return mStatus; }

		void AttachToParent(GameObject* child) { mChildren.push_back(child); }
		void SetParent(GameObject* parent) { mParent = parent; }
		void SetName(const std::string& name) { mName = name; }

		GameObject* GetParent() { return mParent; }
		std::vector<GameObject*> GetChildren() { return mChildren; }

		std::string& GetName() { return mName; }

		std::vector<Component*> GetComponents() { return mComponents; }

		template<typename T>
		inline T* GetComponent()
		{
			T* retrievedComponent = nullptr;
			for (Component* c : mComponents)
			{
				retrievedComponent = dynamic_cast<T*>(c);
				if (retrievedComponent)
					break;
			}
			return retrievedComponent;
		}

		//template<typename T>
		//inline void AddComponent(T* comp)
		//{
		//	Component* c = dynamic_cast<Component*>(comp);
		//	if (!(c->GetGameObject()))
		//	{
		//		c->SetGameObject(this);
		//	}
		//	mComponents.push_back(c);
		//	c->DebugInit();
		//}

		template<typename T>
		inline T* AddComponent(T* comp)
		{
			Component* c = dynamic_cast<Component*>(comp);
			if (!(c->GetGameObject()))
			{
				c->SetGameObject(this);
			}
			mComponents.push_back(c);
			c->DebugInit();

			return comp;
		}

	protected:
		bool mStatus = true; // Enable objects by default

	private:
		std::string mName;

		GameObject* mParent = nullptr;

		std::vector<Component*> mComponents;
		std::vector<GameObject*> mChildren;
	};
}