#pragma once

#include "Components/TransformComp.h"
#include "Components/SpriteComp.h"
#include "Components/TileMapComp.h"
#include "Components/PhysicsComp.h"
#include "Components/ScriptComponent.h"
#include "Components/CameraComp.h"

namespace Engine
{
	enum TYPE
	{
		COMPONENT_TRANSFORM = 0,
		COMPONENT_SPRITE,
		COMPONENT_SCRIPT,
		COMPONENT_AUDIO,
		COMPONENT_CAMERA,
		COMPONENT_TILEMAP,
		COMPONENT_PHYSICS
	};
}
