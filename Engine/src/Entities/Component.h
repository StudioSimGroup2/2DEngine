#pragma once

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

#include "Engine/Core.h"
#include "Common.h"
#include "EngineTime.h"
#include <iostream>

namespace Engine
{
	class GameObject;
	
	class ENGINE_API Component
	{
	public:
		Component();
		virtual ~Component() { mParent = nullptr; }


		virtual void Init() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual void InternalUpdate() = 0;
		virtual void InternalRender() = 0;

		void SetID(int id) { mID = id; }

		int GetType() const { return mType; }
		int GetID() const { return mID; }

		GameObject* GetGameObject() const { return mParent; }
		void SetGameObject(GameObject* parent) { mParent = parent; }

	protected:
		int mType = -1;
		int mID = -1;
		GameObject* mParent = nullptr;
	};
}



