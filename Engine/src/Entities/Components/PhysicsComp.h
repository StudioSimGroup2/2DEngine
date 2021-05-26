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
		PhysicsComp(GameObject* parent);
		~PhysicsComp();
		void Init();
		void Update(float dT);

		void ResetForces();

		void chageGrounded() { /*mGrounded != mGrounded; */; };
		void AddThrust(vec2f thrust);

		float GetMass() { return mMass; }
		float GetGravity() { return mGravity; }
		float GetFriction() { return mFriction; }
		float GetMaxSpeed() { return mMaxSpeed; }
		bool GetGrounded() { return mGrounded; }

		void SetMass(float newMass) { mMass = newMass; }
		void SetGravity(float newGravity) { mGravity = newGravity; }
		void SetFriction(float newFriction) { mFriction = newFriction; }
		void SetMaxSpeed(float newMSpeed) { mMaxSpeed = newMSpeed; }
		void SetGrounded(bool groundedState) { mGrounded = groundedState; }

		std::vector<vec2f> actingForces;

	private:
		void UpdateForces(float dT, vec2f accel);

		bool mGrounded = false;
		vec2f mNetForce;
		vec2f mThrust;
		vec2f mCurrentVelocity;
		vec2f* mPosition;
		float mMass;
		float mWeight;
		float mMaxSpeed = 200.0f;

		float mGravity = 0.98f;
		float mFriction = 0.5f;

		// Inherited via Component
		virtual void Update() override;
		virtual void Render() override;

		// Inherited via Component
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;
	};

}
