#pragma once

#include <vector>
#include <Utils/Math.h>

#include "Common.h"

using namespace std;

struct Node
{
	int ID;
	int parentID;
	vector<int> connectedIDs;
	Vector2D pos;
	float hCost;
	float gCost;
	float fCost;

	vector<int> GetConnectedIDs() { return connectedIDs; };
};

class AI
{
private:
	enum MoveState
	{
		IDLE,
		WANDER,
		PERSUE
	};

	MoveState movementState;
	vector<Node*> AllNodes;
	vector<Vector2D> pathPos;
	vec2f* charPos;

	Node FindStartPoint();
	Node FindNodeWithID(int ID);
	bool NodeInList(Node node, vector<Node> list);
	void UpdateAllNodes(Node node);

public:

	AI(vec2f* position);
	~AI();

	void Update(float deltaTime);
	vector<Vector2D> GetWaypointPositions();

	void CreatePath(int endNodeID);
	void NavigatePath();



	float GetPythag(Vector2D vec1, Vector2D vec2);

};

