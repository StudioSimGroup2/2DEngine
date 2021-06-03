#pragma once

#include "Components/TransformComp.h"
#include "Components/SpriteComp.h"
#include "Components/TileMapComp.h"
#include "Components/PhysicsComp.h"
#include "Components/ScriptComponent.h"
#include "Components/CameraComp.h"
#include "Components/ParticleComp.h"
#include "Components/ObjectCollisionComp.h"
#include "Components/TilemapCollisionComp.h"
#include "Components/LineCollisionComp.h"
#include "Components/LightComp.h"


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
		COMPONENT_PHYSICS,
		COMPONENT_COLBOX,
		COMPONENT_COLTILE,
		COMPONENT_COLLINE,
		COMPONENT_PARTICLE,
		COMPONENT_LIGHT
	};
}
