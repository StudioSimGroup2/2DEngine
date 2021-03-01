#pragma once

#include "Utils/Texture.h"

namespace Engine
{
	class OGLTexture : public Texture
	{
	public:
		OGLTexture(const std::string& name, const std::string& path);
		~OGLTexture();

		virtual void Load(int pos) const override;
		virtual void Unload(int pos) const override;

		virtual const std::string& GetName() const override { return mName; }

	private:
		bool CreateTextureFromFile(const std::string& path);

		unsigned int mID, mBoundSlot = -1;
	};
}

