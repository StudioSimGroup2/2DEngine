#include "OGLTexture.h"

#include <stb/stb_image.h>
#include <Utils\Logger.h>

namespace Engine
{
	OGLTexture::OGLTexture(const std::string& name, const std::string& path)
	{
		mName = name;
		mPath = path;
		
		glGenTextures(1, &mID);

		CreateTextureFromFile();
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

	bool OGLTexture::CreateTextureFromFile()
	{
		int nrChannels;

		unsigned char* source = stbi_load(mPath.c_str(), &mWidth, &mHeight, &nrChannels, 0);

		if (nrChannels == 3)
		{
			int size = mWidth * mHeight * 4;
			unsigned char* temp = new unsigned char[size];

			for (int i = 0; i < mWidth * mHeight; i++)
			{
				temp[i * 4] = source[i * 3];
				temp[i * 4 + 1] = source[i * 3 + 1];
				temp[i * 4 + 2] = source[i * 3 + 2];
				temp[i * 4 + 3] = 255;

				source = temp;
			}
		}

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