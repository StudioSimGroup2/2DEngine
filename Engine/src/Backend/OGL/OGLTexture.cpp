#include "OGLTexture.h"

#include <Glad/glad.h>

#include <stb/stb_image.h>

namespace Engine
{
	OGLTexture::OGLTexture(const std::string& name, const std::string& path)
	{
		mName = name;
		
		glGenTextures(1, &mID);

		CreateTextureFromFile(path);
	}

	OGLTexture::~OGLTexture()
	= default;

	void OGLTexture::Load(int pos) const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	void OGLTexture::Unload(int pos) const
	{
	}

	bool OGLTexture::CreateTextureFromFile(const std::string& path)
	{
		int nrChannels;

		unsigned char* source = stbi_load(path.c_str(), &mWidth, &mHeight, &nrChannels, 0);

		glBindTexture(GL_TEXTURE_2D, mID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(source);

		if (mID)
		{
			return true;
		}

		return false;
	}
}