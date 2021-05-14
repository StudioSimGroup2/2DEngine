#pragma once

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

#include "Engine/Core.h"
#include "Common.h"
#include <iostream>

namespace Engine
{
	class GameObject;
	
	class ENGINE_API Component
	{
	public:
		Component();
		Component(GameObject* parent);

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual ~Component() { mParent = nullptr; }

		std::string GetType() const { return mType; }

		GameObject* GetGameObject() const { return mParent; }
		void SetGameObject(GameObject* parent) { mParent = parent; }

	protected:
		//virtual void Init();
		std::string mType;
		GameObject* mParent = nullptr;
	};
}



