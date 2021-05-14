#pragma once

#include "Common.h"

class Collision
{
private:
	Rect2D collisionBox;
	float boundingRange = 500;
public:
	void SetBoxPosition(Vector2D newPos) { collisionBox.Position = newPos; }
	void SetBoxSize(float width, float height) { collisionBox.width = width; collisionBox.Height = height; }
};

