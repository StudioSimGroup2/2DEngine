#pragma once

#include <GLM/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera()
		: mEye(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)), mAt(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), mUp(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
		mView(glm::mat4(1)), mProjection(glm::mat4(1)), mViewWidth(1280), mViewHeight(720), mMovementSpeed(1.0f), mPrimary(false), mStatic(false) {}

	Camera(glm::vec4 Eye, glm::vec4 At = glm::vec4(0, 0, 0, 1), glm::vec4 Up = glm::vec4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight = 720)
		: mEye(Eye), mAt(At), mUp(Up), mView(glm::mat4(1)), mProjection(glm::mat4(1)),
		mViewWidth(ViewWidth), mViewHeight(ViewHeight), mMovementSpeed(1.0f), mPrimary(false), mStatic(false) {}

	~Camera() = default;

	void Update(float deltaTime) ;  // Updates the view and projection matrices
	void UpdateMovement(float deltaTime);

	inline const glm::vec4 GetEye() const { return mEye; }
	inline const glm::vec4 GetAt() const { return mAt; }
	inline const glm::vec4 GetUp() const { return mUp; }
	inline const glm::mat4 GetViewMatrix() const { return mView; }
	inline const glm::mat4 GetProjectionMatrix() const { return mProjection; }

	inline void SetEye(glm::vec4 Eye) { mEye = Eye; }
	inline void SetAt(glm::vec4 At) { mAt = At; }
	inline void SetUp(glm::vec4 Up) { mUp = Up; }

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

private:
	glm::vec4 mEye, mAt, mUp;
	glm::mat4 mView, mProjection;

	float mViewWidth, mViewHeight;
	float mMovementSpeed;
	bool mPrimary;			// Is this the main camera
	bool mStatic = false;	// Can the camera move? 

};