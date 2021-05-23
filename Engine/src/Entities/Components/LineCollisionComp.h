#pragma once
#include "../Component.h"
#include "Common.h"
#include "../Box2D.h"

namespace Engine
{
	class ENGINE_API LineCollisionComp : public Component
	{
	public:
		LineCollisionComp();
		LineCollisionComp(GameObject* parent);
		~LineCollisionComp();

		void Init();
		float GetLength();

		vec2f GetPoint1() { return point1; }
		vec2f GetPoint2() { return point2; }

		void SetPoint1(vec2f newPoint1) { point1 = newPoint1; }
		void SetPoint2(vec2f newPoint2) { point2 = newPoint2; }


	private:
		vec2f point1, point2;

		//Inherited from Component
		virtual void Update() override;
		virtual void Render() override;
	};
}

