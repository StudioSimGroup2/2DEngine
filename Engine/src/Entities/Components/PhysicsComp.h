#pragma once

#include "../Component.h"

#include <Utils/Math.h>
#include <vector>

namespace Engine
{
	class ENGINE_API PhysicsComp : public Component
	{
	public:
		PhysicsComp();
		~PhysicsComp();

		virtual void Init() override;

		void Update(float dT);

		void ResetForces();

		void chageGrounded() { /*mGrounded != mGrounded; */; };
		void AddThrust(vec2f thrust);

		float GetMass() { return mMass; }
		float GetGravity() { return mGravity; }
		float GetFriction() { return mFriction; }
		float GetMaxSpeed() { return mMaxSpeed; }
		vec2f GetVelocity() { return mCurrentVelocity; }
		bool GetGrounded() { return mGrounded; }

		void SetMass(float newMass) { mMass = newMass; }
		void SetGravity(float newGravity) { mGravity = newGravity; }
		void SetFriction(float newFriction) { mFriction = newFriction; }
		void SetMaxSpeed(float newMaxSpeed) { mMaxSpeed = newMaxSpeed; }
		void SetGrounded(bool newGrounded) { mGrounded = newGrounded; }

		std::vector<vec2f> actingForces;

		// Inherited via Component
		virtual void Update() override;
		virtual void Render() override;

		// Inherited via Component
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

	private:
		void UpdateForces(float dT, vec2f accel);

		bool mGrounded = false;
		vec2f mNetForce;
		vec2f mThrust;
		vec2f mCurrentVelocity;
		vec2f* mPosition;
		float mMass;
		float mWeight;
		float mGravity = 9.8f;
		float mFriction = 0.5f;

		float accumulator = 0;

		float mMaxSpeed = 200.0f;
	};

}
