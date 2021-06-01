#pragma once

#include <Utils/Math.h>

namespace Engine
{
	struct Light
	{
		float radius = 1.0f;
		int type;
		vec2f position;
		float intensity = 1.0f;
	};
}
