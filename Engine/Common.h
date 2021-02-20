#pragma once

#include <vector>

#define SCREENwIDTH 1280
#define SCREENHEIGHT 720

#define TILEWIDTH 32
#define TILEHEIGHT 32


struct Vector2D
{
	float X;
	float Y;

	Vector2D()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vector2D(float initalX, float initalY)
	{
		X = initalX;
		Y = initalY;
	}
};

struct Rect2D
{
	Vector2D Position; //Top right of rectangle
	float width;
	float Height;

	Rect2D()
	{
		Position = Vector2D();
		width = 0;
		Height = 0;
	}
	Rect2D(Vector2D Pos, float W, float H)
	{
		Position = Pos;
		width = W;
		Height = H;
	}

};

typedef std::vector<std::vector<int>> TileMap;