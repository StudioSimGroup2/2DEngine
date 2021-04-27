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
		SpriteComp(GameObject* parent);
		~SpriteComp() override;

		void Update() override;
		void Render() override;

		void SetTexturePath(const std::string path);
		void SetTexture(Texture* texture) { mTexture = texture; }
		Texture* GetTexture() const { return mTexture; }
		
		bool GetFlipX() { return mRenderer->GetFlipX(); }
		bool GetFlipY() { return mRenderer->GetFlipY(); }

		void ToggleFlipX(bool value) { mRenderer->ToggleFlipX(value); }
		void ToggleFlipY(bool value) { mRenderer->ToggleFlipY(value); }

		void SetColour(float r, float g, float b, float a) { mRenderer->SetColour(r, g, b, a); }
		float (&GetColour())[4] { return mRenderer->GetColour(); }

		void* GetTexID();
	private:
		void Init();

		Texture* mTexture = nullptr;
		Renderer2D* mRenderer = nullptr;
	};
}