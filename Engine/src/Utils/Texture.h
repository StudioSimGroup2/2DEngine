#pragma once
#include <string>

namespace Engine
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Load(int pos) const = 0;
		virtual void Unload(int pos) const = 0;

		const std::string& GetName() { return mName; }

	protected:
		std::string mName;
	};

	typedef Texture Texture2D; // :shrug:
}