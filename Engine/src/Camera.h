#pragma once
#include <string>

namespace Engine
{
	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual void Update(float deltaTime) = 0;

		const std::string& GetName() const { return mName; }
		const float GetViewWidth() const { return mViewWidth; }
		const float GetViewHeight() const { return mViewHeight; }
		const float GetSpeed() const { return mMovementSpeed; }
		const bool IsPrimary() const { return mPrimary; }
		const bool IsStatic() const { return mStatic; }

		void SetName(const std::string& name) { mName = name; }
		void SetViewWidth(float width) { mViewWidth = width; }
		void SetViewHeight(float height) { mViewHeight = height; }
		void SetSpeed(float speed) { mMovementSpeed = speed; }
		void SetPrimary(bool flag) { mPrimary = flag; }
		void SetStatic(bool flag) { mStatic = flag; }


	protected:
		void UpdateMovement(float deltaTime);

		std::string mName;
		float mViewWidth, mViewHeight;
		float mMovementSpeed;
		bool mPrimary;
		bool mStatic = false;
	};
}