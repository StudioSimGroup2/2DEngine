#pragma once

#include "Entities\GameObject.h"
#include "Entities\Component.h"
#include "Entities\ComponentIncludes.h"
#include "Common.h"
#include <vector>

class Collision
{
private:
	static bool DoCollisionChecks(Engine::GameObject* object1, Engine::GameObject* object2);

	//Check box against box
	static bool BoxBoxCheck(Engine::GameObject* object1, Engine::GameObject* object2);

	//Check Box against Tilemap Boxes
	static bool BoxTilemapCheck(Engine::GameObject* tilemapBoxes, Engine::GameObject* object);

	//Check Line against Line
	static bool LineLineCheck(Engine::GameObject* line1, Engine::GameObject* line2);
	static bool LineLineCheck(vec2f point1, vec2f point2, vec2f point3, vec2f point4);

	//Check Box against Line
	static bool LineBoxCheck(Engine::GameObject* lineObj, Engine::GameObject* boxObj);

	static float FindDistance(Engine::GameObject* object1, Engine::GameObject* object2);
	static float FindDistance(Box2D box1, Box2D box2);
public:
	static bool CheckCollision(Engine::GameObject* object1, Engine::GameObject* object2);
	static bool CheckTrigger(Engine::GameObject* object1, Engine::GameObject* object2);
};

