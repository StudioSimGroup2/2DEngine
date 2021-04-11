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

		virtual void Draw(vec2f position, Texture* textureToRender) const = 0;
	protected:
		Shader* mShader = nullptr;
	};
}

