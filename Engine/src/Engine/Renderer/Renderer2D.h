#pragma once

#include <Utils/Texture.h>
#include <Utils/Shader.h>
#include <Utils/Math.h>

/// <summary>
/// Sprite Rendering class
/// </summary>

namespace Engine
{
	class Renderer2D
	{
	public:
		virtual ~Renderer2D();

		virtual void Draw(vec2f position, Texture* textureToRender) const = 0;
	protected:
		Shader* mShader;
	};
}

