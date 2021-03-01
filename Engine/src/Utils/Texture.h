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
		virtual int GetWidth() { return mWidth; }
		virtual int GetHeight() { return mHeight; }

	protected:
		std::string mName;

		int mWidth, mHeight;
	};
}