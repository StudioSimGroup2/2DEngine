#pragma once
#include <vector>
#include <iostream>

#include <TinyXML/tinyxml.h>
#include "Common.h"


using namespace std;

class LevelMap
{
public:
	static TileMap LoadLevelMap(char* FilePath);
	static void SaveTileMap(TileMap Map, string Address);
	
	static void EditTile(TileMap* Map, Vector2D Pos, int value) { Map[0][Pos.X][Pos.Y] = value; };

	int getWidth() { return mWidth; };
	int getHeight() { return mHeight; };
private:
	int mWidth;
	int mHeight;
};

