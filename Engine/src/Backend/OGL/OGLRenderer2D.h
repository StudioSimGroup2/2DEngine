#pragma once

#include "Engine/Renderer/Renderer2D.h"

#include <Backend/OGL/OGLShader.h>
#include <Backend/OGL/OGLTexture.h>


namespace Engine
{
	class OGLRenderer2D : public Renderer2D
	{
	public:
		explicit OGLRenderer2D(Shader* shader);

		void Draw(vec2f& position, vec2f& rotation, vec2f& scale, Texture* textureToRender) override;
		
	private:
		void InitBuffers();

		unsigned int mVAO{};
	};
}

