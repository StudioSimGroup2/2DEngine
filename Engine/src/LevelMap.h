#pragma once
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include "Common.h"
#include <tinyxml.h>

using namespace std;

class LevelMap
{
public:
	static TileMap LoadLevelMap(char* FilePath);
	static void SaveTileMap(TileMap Map, string Address);
	int getWidth() { return mWidth; };
	int getHeight() { return mHeight; };
private:
	int mWidth;
	int mHeight;
};

