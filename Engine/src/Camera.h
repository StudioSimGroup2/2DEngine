#pragma once

namespace Engine
{
	class Camera
	{
	public:
		virtual ~Camera() = default;
		
		virtual void Update(float deltaTime) = 0;

		inline const float GetViewWidth() const { return mViewWidth; }
		inline const float GetViewHeight() const { return mViewHeight; }
		inline const float GetSpeed() const { return mMovementSpeed; }
		inline const bool IsPrimary() const { return mPrimary; }
		inline const bool IsStatic() const { return mStatic; }
		inline void SetViewWidth(float width) { mViewWidth = width; }
		inline void SetViewHeight(float height) { mViewHeight = height; }
		inline void SetSpeed(float speed) { mMovementSpeed = speed; }
		inline void SetPrimary(bool flag) { mPrimary = flag; }
		inline void SetStatic(bool flag) { mStatic = flag; }

	protected:
		void UpdateMovement(float deltaTime);

		float mViewWidth, mViewHeight;
		float mMovementSpeed;
		bool mPrimary;
		bool mStatic = false;
	};
}