#pragma once

#include "../Component.h"
#include <Utils/Math.h>
#include <vector>

#define GRAVITY 0.98f
#define FRICTIONCOEF 0.5f

namespace Engine
{
	class ENGINE_API PhysicsComp : public Component
	{
	public:
		PhysicsComp(vec2f* position);
		~PhysicsComp();
		void Update(float dT);

		void ResetForces();

		void chageGrounded() { mGrounded != mGrounded; };
		void AddThrust(vec2f thrust);

		std::vector<vec2f> actingForces;

	private:
		void UpdateForces(float dT);
		void UpdateAcceleration();

		bool mGrounded = true;
		vec2f mNetForce;
		vec2f mThrust;
		vec2f mNetAcceleration;
		vec2f mCurrentVelocity;
		vec2f* mPosition;
		float mMass;
		float mWeight;


		// Inherited via Component
		virtual void Update() override;
		virtual void Render() override;
	};

}
