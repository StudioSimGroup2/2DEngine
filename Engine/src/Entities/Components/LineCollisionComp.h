#pragma once
#include "../Component.h"
#include "Common.h"
#include "Box2D.h"

namespace Engine
{
	class ENGINE_API LineCollisionComp : public Component
	{
	public:
		LineCollisionComp();
		~LineCollisionComp();

		virtual void Init() override;

		float GetLength();

		vec2f GetPoint1() { return point1; }
		vec2f GetPoint2() { return point2; }

		void SetPoint1(vec2f newPoint1) { point1 = newPoint1; }
		void SetPoint2(vec2f newPoint2) { point2 = newPoint2; }

		float GetBRange() { return boundingRange; }
		void SetBRange(float newRange) { boundingRange = newRange; }

		bool GetTrigger() { return isTrigger; }
		void SetTrigger(bool newTrigger) { isTrigger = newTrigger; }

		bool GetColToggle() { return isCollidable; }
		void SetColToggle(bool newColToggle) { isCollidable = newColToggle; }

		//Inherited from Component
		virtual void Update() override;
		virtual void Render() override;

		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

	private:
		bool isCollidable = true;
		bool isTrigger = false;
		float boundingRange = 300;
		vec2f point1, point2;
	};
}

