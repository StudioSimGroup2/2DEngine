#include "Camera.h"

Camera::Camera()
	: mEye(XMFLOAT4(0.0f, 0.0f, -3.0f, 1.0f)), mAt(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)), mUp(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)),
	mView(XMMATRIX()), mProjection(XMMATRIX()), mViewWidth(1280), mViewHeight(720), mMovementSpeed(1.0f), mPrimary(false), mStatic(false)
{
}

Camera::Camera(XMFLOAT4 Eye, XMFLOAT4 At, XMFLOAT4 Up, float ViewWidth, float ViewHeight)
	: mEye(Eye), mAt(At), mUp(Up), mView(XMMATRIX()), mProjection(XMMATRIX()),
	mViewWidth(ViewWidth), mViewHeight(ViewHeight), mMovementSpeed(1.0f), mPrimary(false), mStatic(false)
{
}

void Camera::Update()
{
	if (!mStatic)
		UpdateMovement();

	XMVECTOR Eye = XMLoadFloat4(&mEye);
	XMVECTOR At = XMLoadFloat4(&mAt);
	XMVECTOR Up = XMLoadFloat4(&mUp);

	mView = XMMatrixLookAtLH(Eye, At, Up);
	mProjection = XMMatrixOrthographicLH(mViewWidth, mViewHeight, 0.1, 100); // Need to tweek the quads verts to use this version
}

void Camera::UpdateMovement()
{
#define DT 0.16f // TEMP ASF, Get DT calcs ASAP

	float speed = mMovementSpeed * DT;
	if (GetAsyncKeyState(0x57)) // W key
	{
		mEye.y += speed;
		mAt.y += speed;
	}
	if (GetAsyncKeyState(0x53)) // S key
	{
		mEye.y -= speed;
		mAt.y -= speed;
	}
	if (GetAsyncKeyState(0x41)) // A key
	{
		mEye.x -= speed;
		mAt.x -= speed;
	}
	if (GetAsyncKeyState(0x44)) // D key
	{
		mEye.x += speed;
		mAt.x += speed;
	}
}
