#pragma once


class Camera
{
public:
	Camera();
	Camera(XMFLOAT4 Eye, XMFLOAT4 At = XMFLOAT4(0,0,0,1), XMFLOAT4 Up = XMFLOAT4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight= 720);
	~Camera() = default;

	void Update(float deltaTime);  // Updates the view and projection matrices

	inline const XMFLOAT4 GetEye() const { return mEye; }
	inline const XMFLOAT4 GetAt() const { return mAt; }
	inline const XMFLOAT4 GetUp() const { return mUp; }
	inline const XMMATRIX GetViewMatrix() const { return mView; }
	inline const XMMATRIX GetProjectionMatrix() const { return mProjection; }
	inline const float GetViewWidth() const { return mViewWidth; }
	inline const float GetViewHeight() const { return mViewHeight; }
	inline const float GetSpeed() const { return mMovementSpeed; }
	inline const bool IsPrimary() const { return mPrimary; }
	inline const bool IsStatic() const { return mStatic; }

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
	XMMATRIX mView, mProjection;
	float mViewWidth, mViewHeight;
	float mMovementSpeed;
	bool mPrimary;			// Is this the main camera
	bool mStatic = false;	// Can the camera move? 

	void UpdateMovement(float deltaTime); // TODO: Requires DeltaTime
};
