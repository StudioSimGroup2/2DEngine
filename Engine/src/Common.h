#pragma once

#include <vector>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

#define TILEWIDTH 32
#define TILEHEIGHT 32

//#define ENGINE_RESOURCES_DIR (std::filesystem::absolute(std::filesystem::current_path().parent_path() /= "Engine/Resources/"))
//#define GAME_RESOURCES_DIR (std::filesystem::absolute(std::filesystem::current_path() /= "Resources/"))

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
	
	Vector2D operator /(float a)
	{
		return Vector2D(X / a, Y / a);
	}

	Vector2D operator *(float a)
	{
		return Vector2D(X * a, Y * a);
	}

	Vector2D operator +(Vector2D a)
	{
		return Vector2D(X + a.X, Y + a.Y);
	}

	Vector2D operator -(Vector2D a)
	{
		return Vector2D(X - a.X, Y - a.Y);
	}

	Vector2D operator =(Vector2D a)
	{
		X = a.X;
		Y = a.Y;
		return a;
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


enum SCREENS
{
	SCREEN_TEST = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_LEVEL3,
};