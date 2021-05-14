#include "Camera.h"

#if GRAPHICS_LIBRARY == 0
	#include "Backend\D3D11\D3D11Camera.h"
#elif GRAPHICS_LIBRARY == 1
	#include "Backend\OGL\OpenGLCamera.h"
#endif


Camera::Camera()
	: mEye(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)), mAt(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), mUp(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
	mName("-New Camera-"), mZDepth(1), mViewWidth(1280), mViewHeight(720), mNearPlane(0.1f), mFarPlane(100.0f), mMovementSpeed(100.0f),
	mPrimary(false), mStatic(false)
{
}

Camera* Camera::Create(glm::vec4 Eye, glm::vec4 At, glm::vec4 Up, float ViewWidth, float ViewHeight, const std::string& Name) 
{

#if GRAPHICS_LIBRARY == 0
	return new D3DCamera(Eye, At, Up, ViewWidth, ViewHeight, Name);
#elif GRAPHICS_LIBRARY == 1
	return new OGLCamera(Eye, At, Up, ViewWidth, ViewHeight, Name);
#endif
	
	ASSERT(false, "Could not find camera to match current API selection!");
	return nullptr;
}


void Camera::Lerp(const vec2f from, const vec2f to, float t)
{
	vec2f newPos = Lerp2f(from, to, t);
	mEye.x = newPos.x;
	mEye.y = newPos.y;
}

float Camera::Lerpf(float a, float b, float t)
{
	return a + t * (b - a);
}

vec2f Camera::Lerp2f(vec2f a, vec2f b, float t)
{
	return vec2f(Lerpf(a.x, b.x, t), Lerpf(a.y, b.y, t));
}