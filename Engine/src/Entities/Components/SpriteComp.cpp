#include "SpriteComp.h"
#include <Engine/Renderer/Device.h>
#include <Utils/AssetManager.h>

#include "Entities/GameObject.h"

namespace Engine
{
	SpriteComp::SpriteComp() : Component()
	{
		Init();
	}

	SpriteComp::SpriteComp(GameObject* parent) : Component(parent)
	{
		Init();
	}

	SpriteComp::~SpriteComp()
	{
		if (mTexture)
			mTexture = nullptr;

		if (mRenderer)
		{
			delete mRenderer;
			mRenderer = nullptr;
		}

		Component::~Component();
	}

	void SpriteComp::Update()
	{
		
	}

	void SpriteComp::Render()
	{
		if (!mRenderer)
			return;

#if GRAPHICS_LIBRARY == 0
		dynamic_cast<D3D11Renderer2D*>(mRenderer)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
			mParent->GetComponent<TransformComp>()->GetRotation(),
			mParent->GetComponent<TransformComp>()->GetScale(),
			mTexture
		);
#elif GRAPHICS_LIBRARY == 1
		dynamic_cast<OGLRenderer2D*>(mRenderer)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
			mParent->GetComponent<TransformComp>()->GetRotation(),
			mParent->GetComponent<TransformComp>()->GetScale(),
			mTexture
		);
#endif
	}

	void* SpriteComp::GetTexID()
	{
#if GRAPHICS_LIBRARY == 0
		return dynamic_cast<D3D11Texture*>(mTexture)->GetTexID();

#elif GRAPHICS_LIBRARY == 1
		return dynamic_cast<OGLTexture*>(mTexture)->GetTexID();
#endif
	}

	void SpriteComp::Init()
	{
		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));
		mType = "Sprite";
	}
}
