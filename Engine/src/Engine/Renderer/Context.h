#pragma once

#include <string>

namespace Engine
{
	class Context
	{
	public:
		enum API
		{
			D3D11 = 0
		};

		virtual ~Context() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void Render() = 0;

		virtual int GetCardMemory() = 0;
		virtual std::string GetCardName() = 0;

		static API GetAPI() { return sAPI; }

	private:
		static API sAPI;
	};
}
