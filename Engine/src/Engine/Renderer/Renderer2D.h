#pragma once

#include <Utils/Texture.h>
#include <Utils/Shader.h>
#include <Utils/Math.h>

namespace Engine
{
	class Renderer2D
	{
	public:
		virtual ~Renderer2D() = default;

		virtual void Draw(vec2f& position, vec2f& rotation, vec2f& scale, Texture* textureToRender) = 0;
	protected:
		Shader* mShader = nullptr;
	};
}

