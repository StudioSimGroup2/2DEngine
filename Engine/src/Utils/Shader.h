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

		virtual const std::string& GetName() const = 0;

	protected:
		std::string mName;
	};
}



