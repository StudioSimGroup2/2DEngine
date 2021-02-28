#pragma once

#include "Engine/Renderer/Renderer2D.h"
#include <Backend/OGL/OGLShader.h>

namespace Engine
{
	class OGLRenderer2D : public Renderer2D
	{
	public:
		OGLRenderer2D(OGLShader* shader);

		virtual void Draw(vec2f position, Texture* textureToRender) const override;

	private:
		void InitBuffers();

		unsigned int mVAO;
	};
}

