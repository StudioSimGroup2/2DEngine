#pragma once

#include "../Component.h"
#include "Common.h"
#include "Box2D.h"

namespace Engine
{
	class ENGINE_API ObjectCollisionComp : public Component
	{
	public:
		ObjectCollisionComp();
		~ObjectCollisionComp();

		virtual void Init() override;

		Box2D GetColBox() { return colBox; }

		float GetBRange() { return boundingRange; }
		void SetBRange(float newRange) { boundingRange = newRange; }

		bool GetTrigger() { return isTrigger; }
		void SetTrigger(bool newIsTrigger) { isTrigger = newIsTrigger; }

		// Inherited via Component
		virtual void Update() override;
		virtual void Render() override;

		// Inherited via Component
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

	private:
		bool isTrigger = false;
		float boundingRange = 300;
		Box2D colBox;
	};
}
