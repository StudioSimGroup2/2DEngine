#pragma once

#include "../Component.h"

namespace Engine
{
	class ENGINE_API ScriptComponent : public Component
	{
		ScriptComponent();
		ScriptComponent(GameObject* parent);
		~ScriptComponent() override;

		void Update() override;
		void Render() override;

		void AddScript();
		void RemoveScript();

	private:
		//Script* mScript;

	};
}
