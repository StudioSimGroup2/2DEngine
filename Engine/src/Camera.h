#pragma once
#include <string>
#include <iostream>
#include <Utils\Math.h>
#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>

#include "Engine\Renderer\Context.h"

#if GRAPHICS_LIBRARY == 0 // D3D
	#include <directxmath.h>
#endif
#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }


class Camera
{
public:
	virtual ~Camera() = default;

	static Camera* Create(glm::vec4 Eye, glm::vec4 At = glm::vec4(0, 0, 0, 1), glm::vec4 Up = glm::vec4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight = 720, const std::string& Name = "-New Camera-");
	virtual void Update(float deltaTime) = 0;  // Updates the view and projection matrices

	glm::vec4& GetEye() { return mEye; }
	glm::vec4& GetAt() { return mAt; }
	glm::vec4& GetUp() { return mUp; }
	const glm::vec4 GetEye() const { return mEye; }
	const glm::vec4 GetAt() const { return mAt; }
	const glm::vec4 GetUp() const { return mUp; }
	void SetEye(glm::vec4 Eye) { mEye = Eye; }
	void SetAt(glm::vec4 At) { mAt = At; }
	void SetUp(glm::vec4 Up) { mUp = Up; }

#if GRAPHICS_LIBRARY == 0 // D3D
	virtual const DirectX::XMMATRIX GetViewMatrix() const = 0;
	virtual const DirectX::XMMATRIX GetProjectionMatrix() const = 0;
#elif GRAPHICS_LIBRARY == 1 // OpenGL
	virtual const glm::mat4 GetViewMatrix() const = 0;
	virtual const glm::mat4 GetProjectionMatrix() const = 0;
#endif

	const std::string& GetName() const { return mName; }
	std::string& GetName() { return mName; }
	const float GetZDepth() const { return mZDepth; }
	float& GetZDepth() { return mZDepth; }
	const float GetViewWidth() const { return mViewWidth; }
	float& GetViewWidth() { return mViewWidth; }
	const float GetViewHeight() const { return mViewHeight; }
	float& GetViewHeight() { return mViewHeight; }
	const float GetNearPlane() const { return mNearPlane; }
	float& GetNearPlane() { return mNearPlane; }
	const float GetFarPlane() const { return mFarPlane; }
	float& GetFarPlane() { return mFarPlane; }
	const float GetSpeed() const { return mMovementSpeed; }
	float& GetSpeed() { return mMovementSpeed; }
	const bool IsPrimary() const { return mPrimary; }
	bool& IsPrimary() { return mPrimary; }
	const bool IsStatic() const { return mStatic; }
	bool& IsStatic() { return mStatic; }

	void SetName(const std::string& Name) { mName = Name; }
	void SetViewWidth(float width) { mViewWidth = width; }
	void SetViewHeight(float height) { mViewHeight = height; }
	void SetSpeed(float speed) { mMovementSpeed = speed; }
	void SetPrimary(bool flag) { mPrimary = flag; }
	void SetStatic(bool flag) { mStatic = flag; }

	void Lerp(const vec2f from, const vec2f to, float t);
	float Lerpf(float a, float b, float t);	   // Move to a math lib later
	vec2f Lerp2f(vec2f a, vec2f b, float t);   // Move to a math lib later

protected:
	glm::vec4 mEye, mAt, mUp;
	std::string mName;
	float mZDepth;
	float mViewWidth, mViewHeight;
	float mNearPlane, mFarPlane;
	float mMovementSpeed;
	bool mPrimary;			// Is this the active camera
	bool mStatic;			// Can the camera move? 

	Camera();	// Private as you want to call Camera::Create()!!!
	virtual void UpdateMovement(float deltaTime) = 0;
	
};