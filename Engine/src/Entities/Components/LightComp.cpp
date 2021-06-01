#include "LightComp.h"

#include "../GameObject.h"
#include "LightingManager.h"

namespace Engine
{
	LightComp::LightComp()
	{
	}

	LightComp::~LightComp()
	{
	}

	void LightComp::Init()
	{
		mType = COMPONENT_LIGHT;

		mLight = LightingManager::GetInstance()->AddLight();
	}

	void LightComp::Start()
	{
	}

	void LightComp::Update()
	{
		mLight->position = mParent->GetComponent<TransformComp>()->GetPosition();
	}

	void LightComp::Render()
	{
	}

	void LightComp::InternalUpdate()
	{
		mLight->position = mParent->GetComponent<TransformComp>()->GetPosition();
	}

	void LightComp::InternalRender()
	{
	}

}