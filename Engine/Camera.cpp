#include "Camera.h"

Camera::Camera()
{
	mEye = XMFLOAT4(0.0f, 0.0f, -3.0f, 1.0f);
	mAt = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mUp = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	mView = XMMATRIX();
	mProjection = XMMATRIX();
	mPrimary = false;
}

Camera::Camera(XMFLOAT4 Eye, XMFLOAT4 At, XMFLOAT4 Up)
	: mEye(Eye), mAt(At), mUp(Up)
{
	mView = XMMATRIX();
	mProjection = XMMATRIX();
	mPrimary = false;
}

void Camera::Update()
{
	XMVECTOR Eye = XMLoadFloat4(&mEye);
	XMVECTOR At = XMLoadFloat4(&mAt);
	XMVECTOR Up = XMLoadFloat4(&mUp);

	// 16 & 12 derived from 16:9 aspect ratio, tweeked slightly
	// the higher values = smaller texture size. Lower value = bigger texture size.
	mView = XMMatrixLookAtLH(Eye, At, Up);
	mProjection = XMMatrixOrthographicLH(16, 12, 0.1, 100);
	//mProjection = XMMatrixOrthographicLH(1280, 720, 0.1, 100); // Need to tweek the quads verts to use this version

}