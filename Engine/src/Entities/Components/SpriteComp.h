#pragma once

#include "../Component.h"
#include "Utils/Texture.h"
#include <Engine/Renderer/Renderer2D.h>

namespace Engine
{
	class ENGINE_API SpriteComp : public Component
	{
	public:
		SpriteComp();
		~SpriteComp() override;

		virtual void Init() override;

		void Update() override;
		void Render() override;

		// Inherited via Component
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

		void SetTexturePath(const std::string path);
		void SetSpriteSheetPath(const std::string path, int numOfSprites);
		void SetTexture(Texture* texture) { mTexture = texture; }
		Texture* GetTexture() const { return mTexture; }

		void SetSprite(int posX, int posY);
		vec2i GetSprite() { return mSpritePos; }
		
		bool GetFlipX() { return mRenderer->GetFlipX(); }
		bool GetFlipY() { return mRenderer->GetFlipY(); }

		void ToggleFlipX(bool value) { mRenderer->ToggleFlipX(value); }
		void ToggleFlipY(bool value) { mRenderer->ToggleFlipY(value); }

		void SetColour(float r, float g, float b, float a) { mRenderer->SetColour(r, g, b, a); }
		float (&GetColour())[4] { return mRenderer->GetColour(); }

		void* GetTexID();

	private:
		vec2i mSpritePos;
		Texture* mTexture = nullptr;
		Renderer2D* mRenderer = nullptr;
	};
}