#include "Sprite.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend/D3D11/D3D11Renderer2D.h"
#elif GRAPHICS_LIBRARY == 1
#include "Backend/OGL/OGLRenderer2D.h"
#endif

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
	if (sh == nullptr)
		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));
	else
		mRenderer = Device::CreateRenderer(sh);
}

void Sprite::RemoveRendererComponent()
{
	if (mRenderer)
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
	static_cast<D3D11Renderer2D*>(mRenderer)->Draw(*mPosition, mSprTexture);
#elif GRAPHICS_LIBRARY == 1
	static_cast<OGLRenderer2D*>(mRenderer)->Draw(*mPosition, mSprTexture);
#endif
}