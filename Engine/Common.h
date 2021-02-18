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
typedef std::vector<std::vector<int>> TileMap;