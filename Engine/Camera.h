#pragma once
// TODO: REALLY move to a PCH later...
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(XMFLOAT4 Eye, XMFLOAT4 At = XMFLOAT4(0,0,0,1), XMFLOAT4 Up = XMFLOAT4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight= 720);
	~Camera() = default;

	void Update(float deltaTime);  // Updates the view and projection matrices

	inline const XMFLOAT4 GetEye() const { return mEye; }
	inline XMFLOAT4& GetEye() { return mEye; }
	inline const XMFLOAT4 GetAt() const { return mAt; }
	inline XMFLOAT4& GetAt() { return mAt; }
	inline const XMFLOAT4 GetUp() const { return mUp; }
	inline XMFLOAT4& GetUp() { return mUp; }
	inline float GetZDepth() const { return mZDepth; }
	inline float& GetZDepth() { return mZDepth; }
	inline const XMMATRIX GetViewMatrix() const { return mView; }
	inline const XMMATRIX GetProjectionMatrix() const { return mProjection; }
	inline const float GetViewWidth() const { return mViewWidth; }
	inline float& GetViewWidth() { return mViewWidth; }
	inline const float GetViewHeight() const { return mViewHeight; }
	inline float& GetViewHeight() { return mViewHeight; }
	inline const float GetNearPlane() const { return mNearPlane; }
	inline float& GetNearPlane() { return mNearPlane; }
	inline const float GetFarPlane() const { return mFarPlane; }
	inline float& GetFarPlane() { return mFarPlane; }
	inline const float GetSpeed() const { return mMovementSpeed; }
	inline float& GetSpeed() { return mMovementSpeed; }
	inline const bool IsPrimary() const { return mPrimary; }
	inline bool& IsPrimary() { return mPrimary; }
	inline const bool IsStatic() const { return mStatic; }
	inline bool& IsStatic() { return mStatic; }

	inline void SetEye(XMFLOAT4 Eye) { mEye = Eye; }
	inline void SetAt(XMFLOAT4 At) { mAt = At; }
	inline void SetUp(XMFLOAT4 Up) { mUp = Up; }
	inline void SetViewWidth(float width) { mViewWidth = width; }
	inline void SetViewHeight(float height) { mViewHeight = height; }
	inline void SetSpeed(float speed) { mMovementSpeed = speed; }
	inline void SetPrimary(bool flag) { mPrimary = flag; }
	inline void SetStatic(bool flag) { mStatic = flag; }

private:
	XMFLOAT4 mEye, mAt, mUp;
	float mZDepth;	
	XMMATRIX mView, mProjection;
	float mViewWidth, mViewHeight;
	float mNearPlane, mFarPlane;
	float mMovementSpeed;
	bool mPrimary;			// Is this the main camera
	bool mStatic;			// Can the camera move? 

	void UpdateMovement(float deltaTime); // TODO: Requires DeltaTime
};
