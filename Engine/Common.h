#pragma once

#define SCREENwIDTH 1280
#define SCREENHEIGHT 720

#define TILEWIDTH 32
#define TILEHEIGHT 32


struct Vector2D
{
	float X;
	float Y;
};
typedef std::vector<std::vector<int>> TileMap;