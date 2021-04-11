#pragma once

#include "../Component.h"
#include "Sprite.h"

namespace Engine
{
	class ENGINE_API SpriteComp : public Component
	{
	public:
		SpriteComp() : Component() { mType = "Sprite"; }
		SpriteComp(GameObject* parent) : Component(parent) { mType = "Sprite"; }
		~SpriteComp() override;

		void Update() override;
		void Render() override;

		void SetSprite(Sprite* sprite) { mSprite = sprite; }
		Sprite* GetSprite() { return mSprite; }

	private:
		Sprite* mSprite = nullptr;
	};
}