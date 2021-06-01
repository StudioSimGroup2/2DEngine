#include "LightingManager.h"
#include "Engine/Renderer/Device.h"
#include "Utils/AssetManager.h"

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
		mFrameBuffer.OverrideColour(0.0f, 0.0f, 0.0f, 0.0f);

		mTexture = AssetManager::GetInstance()->LoadTexture("Light", "Assets/Textures/Light.png");
	}

	void LightingManager::Render()
	{
		mFrameBuffer.Load();

		int count = 0;

		for (auto l : mLights)
		{
			mRenderers.at(count)->Draw(l.position, vec2f(0.0f), vec2f(l.radius), mTexture);
			count++;
		}

		mFrameBuffer.Unload();
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

