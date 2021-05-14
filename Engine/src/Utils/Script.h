#pragma once
#include <string>
#include <sol.hpp>

namespace Engine
{
	class GameObject;

	class Script
	{
	public:
		Script();
		~Script();

		void Load(const std::string& name, const std::string& mPath);

		void CallStart(GameObject* parent);
		void CallUpdate(GameObject* parent);
		void CallRender(GameObject* parent);
	private:
		sol::protected_function mStart;
		sol::protected_function mUpdate;
		sol::protected_function mRender;
	};
}

