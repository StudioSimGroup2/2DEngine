#include "ObjectCollisionComp.h"
#include "Entities\GameObject.h"

Engine::ObjectCollisionComp::ObjectCollisionComp()
{
}

Engine::ObjectCollisionComp::~ObjectCollisionComp()
{
}

void Engine::ObjectCollisionComp::Init()
{
	mType = COMPONENT_COLBOX;
	vec2f position = mParent->GetComponent<TransformComp>()->GetPosition();
	colBox.SetPosition(position);

	vec2f size = (32.0f, 32.0f);
	colBox.SetSize(size);

	mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));
	mTexture = AssetManager::GetInstance()->LoadTexture("BoxColIcon", "Assets/Textures/BoxColIcon.png");
}

void Engine::ObjectCollisionComp::Update()
{
	colBox.SetPosition(mParent->GetComponent<TransformComp>()->GetPosition());
}

void Engine::ObjectCollisionComp::Render()
{
}

void Engine::ObjectCollisionComp::Start()
{
}

void Engine::ObjectCollisionComp::InternalUpdate()
{
	colBox.SetPosition(mParent->GetComponent<TransformComp>()->GetPosition());
}

void Engine::ObjectCollisionComp::InternalRender()
{
	vec2f scale;
	if (mParent->GetComponent<SpriteComp>()->GetTexture() == nullptr)
	{
		scale.x = colBox.GetSize().x / 32.0f;
		scale.y = colBox.GetSize().y / 32.0f;
	}
	else
	{
		scale.x = colBox.GetSize().x / mParent->GetComponent<SpriteComp>()->GetTexture()->GetWidth();
		scale.y = colBox.GetSize().y / mParent->GetComponent<SpriteComp>()->GetTexture()->GetHeight();
	}


#if GRAPHICS_LIBRARY == 0
	dynamic_cast<D3D11Renderer2D*>(mRenderer)->Draw(colBox.GetPosition(),
		mParent->GetComponent<TransformComp>()->GetRotation(),
		scale, mTexture);
#elif GRAPHICS_LIBRARY == 1
	dynamic_cast<OGLRenderer2D*>(mRenderer)->Draw(colBox.GetPosition(),
		mParent->GetComponent<TransformComp>()->GetRotation(),
		scale, mTexture);
#endif
}
