#include "OGLTexture.h"

#include <Glad/glad.h>

namespace Engine
{
	OGLTexture::OGLTexture(const std::string& name, const std::string& path)
	{
		mName = name;
		
		glGenTextures(1, &mID);

		CreateTextureFromFile(path);
	}

	OGLTexture::~OGLTexture()
	{
	}

	void OGLTexture::Load(int pos) const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	void OGLTexture::Unload(int pos) const
	{
	}

	bool OGLTexture::CreateTextureFromFile(const std::string& path)
	{
		glBindTexture(GL_TEXTURE_2D, mID);

		// Load Image data !!!

		glBindTexture(GL_TEXTURE_2D, 0);
		
		return false;
	}
}