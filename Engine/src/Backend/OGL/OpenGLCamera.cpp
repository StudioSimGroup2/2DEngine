#include <Backend/OGL/OpenGLCamera.h>

void Camera::Update(float deltaTime)
{
	if (!mStatic)
		UpdateMovement(deltaTime);

	// Force the cameras At to be where the eye is
	mAt.x = mEye.x;
	mAt.y = mEye.y;

	mView = glm::lookAt(glm::vec3(mEye), glm::vec3(mAt), glm::vec3(mUp));
	mProjection = glm::orthoLH(0.0f, mViewWidth, mViewHeight, 0.0f, -1.0f, 1.0f);
}

void Camera::UpdateMovement(float deltaTime)
{
	//float speed = mMovementSpeed * deltaTime;
	//if (GetAsyncKeyState(0x57)) // W key
	//{
	//	mEye.y -= speed;
	//}
	//if (GetAsyncKeyState(0x53)) // S key
	//{
	//	mEye.y += speed;
	//}
	//if (GetAsyncKeyState(0x41)) // A key
	//{
	//	mEye.x += speed;
	//}
	//if (GetAsyncKeyState(0x44)) // D key
	//{
	//	mEye.x -= speed;
	//}
}
