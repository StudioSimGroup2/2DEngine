#include "Sprite.h"

using namespace Engine;

Sprite::Sprite(char* name, vec2f* position, Texture* tex)
{
	mPosition = position;
	mName = name;

	mSprTexture = tex;
}

Sprite::Sprite(char* name, vec2f* position, char* texName, char* texPath)
{
	mPosition = position;
	mName = name;
	
	mSprTexture = AssetManager::GetInstance()->LoadTexture(texName, texPath);
}

Sprite::~Sprite()
{
	RemoveRendererComponent();

	if (mPosition)
	{
		delete mPosition;
		mPosition = nullptr;
	}
}

void Sprite::AddRendererComponent(Shader* sh)
{
	mRenderer = Device::CreateRenderer(sh == nullptr ? AssetManager::GetInstance()->GetShaderByName("Default") : sh);
}

void Sprite::RemoveRendererComponent()
{
	delete mRenderer;
	
	mRenderer = nullptr;
}

void Sprite::Update(float deltaTime)
{

}

void Sprite::Draw()
{
	if (!mRenderer)
		return;

#if GRAPHICS_LIBRARY == 0
	dynamic_cast<D3D11Renderer2D*>(mRenderer)->Draw(*mPosition, mSprTexture);
#elif GRAPHICS_LIBRARY == 1
	dynamic_cast<OGLRenderer2D*>(mRenderer)->Draw(*mPosition, mSprTexture);
#endif
}