#pragma once
#include <string>

namespace Engine
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Load(int pos = 0) const = 0;
		virtual void Unload(int pos = 0) const = 0;

		const std::string& GetName() { return mName; }
		const std::string& GetPath() { return mPath; }

		void SetName(const std::string& name) { mName = name; }
		void SetPath(const std::string& path) { mPath = path; }

		virtual int GetWidth() { return mWidth; }
		virtual int GetHeight() { return mHeight; }

		virtual void* GetTexID() = 0;

		bool IsSpriteSheet() { return mMultiple; }

		void SetMultiple(bool option) { mMultiple = option; }

		int GetNumOfSprites() { return mNumOfSprites; }

		void SetNumOfSprites(int value) { mNumOfSprites = value; }

		void SetSpriteWidth(int value) { mSpriteWidth = value; }
		void SetSpriteHeight(int value) { mSpriteHeight = value; }

		int GetSpriteHeight() { return mSpriteHeight; }
		int GetSpriteWidth() { return mSpriteWidth; }

	protected:
		bool mMultiple;
		int mNumOfSprites;
		int mSpriteWidth, mSpriteHeight;

		std::string mPath;
		std::string mName;

		int mWidth, mHeight;
	};
}