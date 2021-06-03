#pragma once

#include "Utils\Math.h"
class Box2D
{
public:
	void SetPosition(vec2f newPos) { position = newPos; }
	void SetSize(vec2f newSize) { size = newSize; }

	vec2f& GetPosition() { return position; }
	vec2f& GetSize() { return size; }

private:
	vec2f position;
	vec2f size;
};

