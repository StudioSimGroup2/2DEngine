#include <Engine/Core.h>

namespace Engine
{
	class ENGINE_API ScriptingEngine
	{
	public:

		void Init();

		static void Shutdown();

		static ScriptingEngine* GetInstance();

	private:
		ScriptingEngine() {}

		static ScriptingEngine* mInstance;
	};
}