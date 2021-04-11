#include "Component.h"
#include "GameObject.h"

namespace Engine
{
	Component::Component()
	{
	}

	Component::Component(GameObject* parent)
	{
		mParent = parent; 
	}
}