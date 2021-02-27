#pragma once
#include <string>

namespace Engine
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Load(int pos = 1) const = 0;
		virtual void Unload(int pos = 1) const = 0;

		virtual const std::string& GetName() const = 0;

	protected:
		std::string mName;
	};

	typedef Texture Texture2D; // :shrug:
}