#pragma once

#include <vector>
#include "Common.h"
#include "Character.h"

using namespace std;

class AI : public Character
{
	struct Waypoint
	{
		int ID;
		Vector2D pos;
	};

	struct Node
	{
		int parentID;
		Waypoint waypoint;
		float hCost;
		float gCost;
		float fCost;
	};

	enum MoveState
	{
		IDLE,
		WANDER,
		PERSUE
	};

private:

	MoveState movementState;
	vector<Node> nodes;
	vector<Vector2D> pathPos;
	vec2f* CharPos;

	void FindStartPoint();

public:

	AI(vec2f* position);
	~AI();

	void Update(float deltaTime);
	vector<Vector2D> GetWaypointPositions();

	void CreatePath(int endNodeID);
	void NavigatePath();

};

