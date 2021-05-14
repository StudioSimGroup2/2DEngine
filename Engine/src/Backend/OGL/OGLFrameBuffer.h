#pragma once

#include <Glad\glad.h>

namespace Engine
{
	class OGLFrameBuffer
	{
	public:
		OGLFrameBuffer(unsigned int width, unsigned int height);
		~OGLFrameBuffer();

		void Load();
		void Unload();

		void* GetTexID() { return(void*)(size_t)mTexture; }

	private:
		GLuint mID;

		GLuint mTexture;
	};

}
