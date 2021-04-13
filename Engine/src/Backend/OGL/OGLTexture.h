#pragma once

#include <Glad/glad.h>
#include "Utils/Texture.h"

#define STB_IMAGE_IMPLEMENTATION

namespace Engine
{
	class OGLTexture : public Texture
	{
	public:
		OGLTexture(const std::string& name, const std::string& path);
		~OGLTexture();

		void Load(int pos) const override;
		void Unload(int pos) const override;

		virtual void* GetTexID() override { return(void*)(size_t)mID; }

	private:
		bool CreateTextureFromFile();

		GLuint mID;

	};
}

