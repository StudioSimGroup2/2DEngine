#include "Camera.h"

Camera::Camera()
{
	mEye = XMFLOAT4(0.0f, 0.0f, -3.0f, 1.0f);
	mAt = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mUp = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
}

Camera::Camera(XMFLOAT4 Eye, XMFLOAT4 At, XMFLOAT4 Up)
	: mEye(Eye), mAt(At), mUp(Up)
{
}

void Camera::Update()
{
	XMVECTOR Eye = XMLoadFloat4(&mEye);
	XMVECTOR At = XMLoadFloat4(&mAt);
	XMVECTOR Up = XMLoadFloat4(&mUp);

	mView = XMMatrixLookAtLH(Eye, At, Up);
	mProjection = XMMatrixOrthographicLH(16, 12, 0.1, 100);
}