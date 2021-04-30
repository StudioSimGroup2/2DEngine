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

		const std::string& const GetName() { return mName; }
		const std::string& const GetPath() { return mPath; }
		virtual int GetWidth() { return mWidth; }
		virtual int GetHeight() { return mHeight; }

		virtual void* GetTexID() = 0;

	protected:
		std::string mPath;
		std::string mName;

		int mWidth, mHeight;
	};
}