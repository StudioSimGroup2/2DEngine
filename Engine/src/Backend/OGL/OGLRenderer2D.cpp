#include "OGLRenderer2D.h"

namespace Engine
{
	OGLRenderer2D::OGLRenderer2D(OGLShader* shader)
	{
		mShader = static_cast<Shader*>(shader);
	}

	void OGLRenderer2D::Draw(vec2f position, Texture* textureToRender) const
	{
		mShader->Load();
		textureToRender->Load();
	}

	void OGLRenderer2D::InitBuffers()
	{
		
	}
}
