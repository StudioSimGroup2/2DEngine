#pragma once
#include "Engine/Renderer/FrameBuffer.h"
#include <vector>
#include <Engine/Light.h>
#include <Engine/Renderer/Renderer2D.h>

namespace Engine
{
	class LightingManager
	{
	public:
		static LightingManager* GetInstance();

		void Init();

		void Render(FrameBuffer &frameBuffer);

		Light* AddLight();

		static void Shutdown();

		FrameBuffer& GetFinalFB() { return mFinal; }
		FrameBuffer& GetLightFB() { return mFrameBuffer; }

		void* GetRenderToTexID() { return mFrameBuffer.GetTexID(); }

	private:
		LightingManager() {}

		static LightingManager* mInstance;

		std::vector<Light> mLights;
		std::vector<Renderer2D*> mRenderers;

		FrameBuffer mFrameBuffer;
		FrameBuffer mFinal;

		Texture* mTexture;

		Shader* mShader;

	};
}