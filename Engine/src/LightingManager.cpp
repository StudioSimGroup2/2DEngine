#include "LightingManager.h"
#include "Engine/Renderer/Device.h"
#include "Utils/AssetManager.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend/D3D11/D3D11Shader.h"
#elif GRAPHICS_LIBRARY == 1

#endif

namespace Engine
{
	LightingManager* LightingManager::mInstance = nullptr;
	
	LightingManager* LightingManager::GetInstance()
	{
		if (!mInstance)
			mInstance = new LightingManager();

		return mInstance;
	}

	void LightingManager::Init()
	{
		mFrameBuffer.CreateFrameBuffer(1260, 677);
		mFinal.CreateFrameBuffer(1260, 677);

		mFrameBuffer.Get()->PrepareBuffers();

		mTexture = AssetManager::GetInstance()->LoadTexture("Light", "Assets/Textures/Light.png");

		mShader = AssetManager::GetInstance()->LoadShader("Lighting", "Assets/Shaders/lighting.fx");
	}

	void LightingManager::Render(FrameBuffer &frameBuffer)
	{
		mFrameBuffer.Load();

		int count = 0;

		for (auto l : mLights)
		{
			mRenderers.at(count)->Draw(l.position, vec2f(0.0f), vec2f(l.radius), mTexture);
			count++;
		}

		mFrameBuffer.Unload();
		
		mShader->Load();

		dynamic_cast<D3D11Shader*>(mShader)->PassTextureToPS(0, frameBuffer.Get()->GetSRV());
		dynamic_cast<D3D11Shader*>(mShader)->PassTextureToPS(1, mFrameBuffer.Get()->GetSRV());

		mFinal.Load();
		mFrameBuffer.Get()->Draw();
		mFinal.Unload();

		mShader->Unload();
	}

	Light* LightingManager::AddLight()
	{
		mLights.push_back(Light());
		
		mRenderers.push_back(Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default")));

		return &mLights.back();
	}

	void LightingManager::Shutdown()
	{
		mInstance->mLights.clear();
	}

}

