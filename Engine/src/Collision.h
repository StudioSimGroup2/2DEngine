#pragma once

#include "Entities\GameObject.h"
#include "Entities\Component.h"
#include "Entities\ComponentIncludes.h"
#include "Common.h"
#include <vector>

class Collision
{
private:
	float boundingRange = 300;

public:

	float GetBRange() { return boundingRange; }
	void SetBRange(float newRange) { boundingRange = newRange; }

	bool Update(std::vector<Engine::GameObject*> gameObjects);

};

