#pragma once

#include "Engine/Core.h"
#include <iostream>

namespace Engine
{
	class GameObject;

	class ENGINE_API Component
	{
	public:
		Component() { }
		Component(GameObject* parent) { mParent = parent; }

		void DebugInit() { std::cout << "[" << mType << "]The abyss will gaze into thee: " << mParent << std::endl; }

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual ~Component() { mParent = nullptr; }

		const std::string GetType() const { return mType; }

		GameObject* GetGameObject() { return mParent; }
		void SetGameObject(GameObject* parent) { mParent = parent; }

	protected:
		std::string mType;
	private:
		GameObject* mParent = nullptr;
	};
}



