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

		void SetTexture(Texture* texture) { mTexture = texture; }
		Texture* GetTexture() const { return mTexture; }

		void* GetTexID();
	private:
		void Init();

		Texture* mTexture = nullptr;
		Renderer2D* mRenderer = nullptr;
	};
}