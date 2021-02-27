#include "Sprite.h"

#if GRAPHICS_LIBRARY == 0
#include "Backend/D3D11/D3D11Renderer2D.h"
#elif GRAPHICS_LIBRARY == 1
#endif

using namespace Engine;

Sprite::Sprite(Device* dev, const std::string& name, const std::string& path, vec2f position)
{
	mPosition = position;
	mName = name;

	mSprTexture = AssetManager::GetInstance()->LoadTexture(dev, "Texture: " + name, path);
}

Sprite::~Sprite()
{
	
}

void Sprite::AddRendererComponent(Renderer2D* renderer)
{
	mRenderer = renderer;
}

void Sprite::Update(float deltaTime)
{

}

void Sprite::Draw()
{
#if GRAPHICS_LIBRARY == 0
	static_cast<D3D11Renderer2D*>(mRenderer)->Draw(mPosition, mSprTexture);
#elif GRAPHICS_LIBRARY == 1
#endif
}