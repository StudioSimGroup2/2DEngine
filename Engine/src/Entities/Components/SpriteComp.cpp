#include "SpriteComp.h"

namespace Engine
{
	SpriteComp::~SpriteComp()
	{
		if (mSprite)
		{
			delete mSprite;
			mSprite = nullptr;
		}

		Component::~Component();
	}

	void SpriteComp::Update()
	{
		
	}

	void SpriteComp::Render()
	{
		mSprite->Draw();
	}
}
