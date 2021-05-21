#include "Camera.h"

namespace Engine
{
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
}