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

		void Start() { mScript.CallStart(mParent); }
		void Update() override;
		void Render() override;

		std::string& GetFile() { return mPath; }

		void AddScript(const std::string& file);
		void RemoveScript() { mPath.clear(); };

		std::string getpath() { return mPath; };
		void Setpath(std::string path) { mPath = path; };

	private:
		void Init();

		std::string mPath;

		Script mScript;

		// Inherited via Component
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;
	};
}
