#pragma once

#include "Entities\GameObject.h"
#include "Entities\ComponentIncludes.h"
#include "Common.h"
#include <vector>

class Collision
{
private:
	float boundingRange = 300;

public:
	void Update(std::vector<Engine::GameObject*> gameObjects);

};

