#pragma once
#include <string>

#include "Engine/Defines.h"

namespace Engine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Load() const = 0;
		virtual void Unload() const = 0;

		const std::string& GetName() { return mName; }

	protected:
		std::string mName;
	};
}



