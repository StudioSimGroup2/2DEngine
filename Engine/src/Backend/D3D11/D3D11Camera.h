#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
#include <string>
using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(XMFLOAT4 Eye, XMFLOAT4 At = XMFLOAT4(0, 0, 0, 1), XMFLOAT4 Up = XMFLOAT4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight = 720, const std::string& Name="-New Camera-");
	~Camera() = default;

	void Update(float deltaTime);  // Updates the view and projection matrices

	const XMFLOAT4 GetEye() const { return mEye; }
	XMFLOAT4& GetEye() { return mEye; }
	const XMFLOAT4 GetAt() const { return mAt; }
	XMFLOAT4& GetAt() { return mAt; }
	const XMFLOAT4 GetUp() const { return mUp; }
	XMFLOAT4& GetUp() { return mUp; }
	const std::string& GetName() const { return mName; }
	std::string& GetName() { return mName; }
	const float GetZDepth() const { return mZDepth; }
	float& GetZDepth() { return mZDepth; }
	const XMMATRIX GetViewMatrix() const { return mView; }
	const XMMATRIX GetProjectionMatrix() const { return mProjection; }
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

	void SetEye(XMFLOAT4 Eye) { mEye = Eye; }
	void SetAt(XMFLOAT4 At) { mAt = At; }
	void SetUp(XMFLOAT4 Up) { mUp = Up; }
	void SetName(const std::string& Name) { mName = Name; }
	void SetViewWidth(float width) { mViewWidth = width; }
	void SetViewHeight(float height) { mViewHeight = height; }
	void SetSpeed(float speed) { mMovementSpeed = speed; }
	void SetPrimary(bool flag) { mPrimary = flag; }
	void SetStatic(bool flag) { mStatic = flag; }

private:
	XMFLOAT4 mEye, mAt, mUp;
	std::string mName;
	float mZDepth;	
	XMMATRIX mView, mProjection;
	float mViewWidth, mViewHeight;
	float mNearPlane, mFarPlane;
	float mMovementSpeed;
	bool mPrimary;			// Is this the main camera
	bool mStatic;			// Can the camera move? 

	void UpdateMovement(float deltaTime); // TODO: Requires DeltaTime
};