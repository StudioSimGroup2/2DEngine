#pragma once
#include <vector>

#include "Engine/Core.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Input/InputManager.h"
#include "Utils/AssetManager.h"
#include "Utils/Logger.h"
#include "Component.h"
#include "ComponentIncludes.h"

#include <iostream>

namespace Engine
{
	class ENGINE_API GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Start();
		void Update();
		void Render();

		void InternalUpdate();
		void InternalRender();

		void Attach(GameObject* parent);
		void RemoveParent();

		void EnableObject() { mStatus = true; }
		void DisableObject() { mStatus = false; }
		bool IsEnabled() { return mStatus; }

		void SetName(const std::string& name) { if (!name.empty()) mName = name; }

		GameObject* GetParent() const { return mParent; }
		void SetParent(GameObject* go) { mParent = go; };
		void RemoveChild(GameObject* go);
		std::vector<GameObject*> GetChildren() { return mChildren; }

		std::string& GetName() { return mName; }

		std::vector<Component*> GetComponents() const { return mComponents; }

		std::vector<GameObject*>::iterator begin() { return mChildren.begin(); }
		std::vector<GameObject*>::iterator end() { return mChildren.end(); }

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

		template<typename T>
		inline T* AddComponent(T* comp)
		{
			Component* c = dynamic_cast<Component*>(comp);
			if (!(c->GetGameObject()))
			{
				c->SetGameObject(this);
				mComponentID++;
				c->SetID(mComponentID);
				c->Init();
			}
			mComponents.push_back(c);

			return comp;
		}
		inline void RemoveComponent(Component* Comp)
		{
			int i = 0;
			for (Component* Test : mComponents)
			{
				if (Test == Comp)
				{
					mComponents.erase(mComponents.begin() + i);
					delete Test;
					Test = nullptr;
					break;
				}
				i++;
			}
		}
		void AddChild(GameObject* go) { mChildren.push_back(go); }

	protected:
		bool mStatus = true; // Enable objects by default
		GameObject* mParent = nullptr;

	private:
		void InitTransformComponent();
		
		std::string mName;

		static int mComponentID;

		std::vector<Component*> mComponents;
		std::vector<GameObject*> mChildren;
	};
}