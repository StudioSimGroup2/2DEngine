#include <Backend/D3D11/D3D11Camera.h>

Camera::Camera()
	: mEye(XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f)), mAt(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)), mUp(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)), mName("-New Camera-"),
	mZDepth(1), mView(XMMATRIX(XMMatrixIdentity())), mProjection(XMMATRIX(XMMatrixIdentity())), mViewWidth(1280), mViewHeight(720), 
	mNearPlane(0.1f), mFarPlane(100.0f), mMovementSpeed(100.0f), mPrimary(false), mStatic(false)
{
}

Camera::Camera(XMFLOAT4 Eye, XMFLOAT4 At, XMFLOAT4 Up, float ViewWidth, float ViewHeight, const std::string& Name)
	: mEye(Eye), mAt(At), mUp(Up), mName(Name), mZDepth(1), mView(XMMATRIX(XMMatrixIdentity())), mProjection(XMMATRIX(XMMatrixIdentity())),
	mViewWidth(ViewWidth), mViewHeight(ViewHeight), mNearPlane(0.1f), mFarPlane(100.0f), 
	mMovementSpeed(100.0f), mPrimary(false), mStatic(false)
{
}

void Camera::Update(float deltaTime)
{
	if (!mStatic)
		UpdateMovement(deltaTime);

	// Force the cameras at to be where the eye is, otherwise we get some weird skewing.
	mAt.x = mEye.x;
	mAt.y = mEye.y;
	if (mZDepth < 0.0f)	// Cameras shouldn't have a negitive z-depth. It will result in the scene being fliped!
		mZDepth = 0.0f;

	mEye.z = -mZDepth; // Flip the z-depth, Higher Z-depth = object will render infront of others!
	mAt.z = 0.001f;

	XMVECTOR Eye = XMLoadFloat4(&mEye);
	XMVECTOR At = XMLoadFloat4(&mAt);
	XMVECTOR Up = XMLoadFloat4(&mUp);

	mView = XMMatrixLookAtLH(Eye, At, Up);
	mProjection = XMMatrixOrthographicLH(mViewWidth, mViewHeight, mNearPlane, mFarPlane); // Need to tweek the quads verts to use this version
}

void Camera::UpdateMovement(float deltaTime)
{
	float speed = mMovementSpeed * deltaTime;
	if (GetAsyncKeyState(0x57)) // W key
	{
		mEye.y += speed;
	}
	if (GetAsyncKeyState(0x53)) // S key
	{
		mEye.y -= speed;
	}
	if (GetAsyncKeyState(0x41)) // A key
	{
		mEye.x -= speed;
	}
	if (GetAsyncKeyState(0x44)) // D key
	{
		mEye.x += speed;
	}
}