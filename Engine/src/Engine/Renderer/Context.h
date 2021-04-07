#pragma once

#include <string>

namespace Engine
{
	class Context
	{
	public:

		virtual ~Context() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void SwapBuffers() = 0;

		virtual int GetCardMemory() = 0;
		virtual std::string GetCardName() = 0;
	};
}
