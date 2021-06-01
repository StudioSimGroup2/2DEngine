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

		void ToggleFlipX(bool val) { mFlipX = val; }
		void ToggleFlipY(bool val) { mFlipY = val; }

		bool GetFlipX() const { return mFlipX; }
		bool GetFlipY() const { return mFlipY; }

		virtual void UpdateBuffers(int totalWidth, int totalHeight, int posX, int posY) = 0;

		void SetColour(float r, float g, float b, float a) { mColour[0] = r; mColour[1] = g; mColour[2] = b; mColour[3] = a; }

		float (&GetColour())[4] { return mColour; }
	protected:
		Shader* mShader = nullptr;

		bool mFlipX = false;
		bool mFlipY = false;
		
		float mColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}

