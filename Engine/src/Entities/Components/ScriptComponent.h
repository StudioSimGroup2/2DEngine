#pragma once

#include "../Component.h"
#include "Utils\Script.h"


namespace Engine
{
	class ENGINE_API ScriptComp : public Component
	{
	public:
		ScriptComp();
		ScriptComp(GameObject* parent);
		~ScriptComp() override;

		void Update() override;
		void Render() override;

		std::string& GetFile() { return mPath; }

		void AddScript(const std::string& file);
		void RemoveScript() { mPath.clear(); };

	private:
		void Init();

		std::string mPath;

		Script mScript;
	};
}
