#include "SpriteComp.h"
#include <Engine/Renderer/Device.h>
#include <Utils/AssetManager.h>

#include "Entities/GameObject.h"

namespace Engine
{
	SpriteComp::SpriteComp()
	{
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

		mParent = nullptr;
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

	void SpriteComp::SetTexturePath(const std::string path)
	{
		SetTexture(AssetManager::GetInstance()->LoadTexture(mParent->GetName() + " Tex", path));

		if (mRenderer)
			delete mRenderer;

		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));
	}

	void SpriteComp::SetSpriteSheetPath(const std::string path, int numOfSprites)
	{
		SetTexture(AssetManager::GetInstance()->LoadSpriteSheet(mParent->GetName() + " Tex", path, numOfSprites));

		if (mRenderer)
			delete mRenderer;

		mRenderer = Device::CreateSpriteSheetRenderer(AssetManager::GetInstance()->GetShaderByName("Default"), mTexture->GetWidth(), mTexture->GetHeight(), mSpritePos);
	}

	void SpriteComp::SetSprite(int posX, int posY)
	{
		if (!mTexture->IsSpriteSheet())
			return;
		
		mSpritePos = vec2i(posX, posY);

		mRenderer->UpdateBuffers(mTexture->GetWidth(), mTexture->GetHeight(), mSpritePos.x, mSpritePos.y);
	}

	void* SpriteComp::GetTexID()
	{
		if (!mTexture)
			return nullptr;

#if GRAPHICS_LIBRARY == 0
		return dynamic_cast<D3D11Texture*>(mTexture)->GetTexID();

#elif GRAPHICS_LIBRARY == 1
		return dynamic_cast<OGLTexture*>(mTexture)->GetTexID();
#endif
	}

	void SpriteComp::Init()
	{
		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));

		mType = COMPONENT_SPRITE;
	}

	void SpriteComp::Start()
	{
	}

	void SpriteComp::InternalUpdate()
	{
	}

	void SpriteComp::InternalRender()
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
}
