#pragma once

#include "Entities\ComponentIncludes.h"

namespace Engine
{
	class GameObject;
	
	class InspectorWidget
	{
	public:
		InspectorWidget();
		~InspectorWidget();

		void Render(GameObject* go);

	private:
		void RenderTransformComponent(TransformComp* c);
		void RenderSpriteComponent(SpriteComp* c);
		void RenderPhysicsComponent(PhysicsComp* c);
		void RenderScriptComponent(ScriptComp* c);
		void TileMapComponent(TileMapComp* c);
	};
}
