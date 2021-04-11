#pragma once

#include "../../TinyXML/src/tinyxml.h"

#include <iostream>
#include <sstream>

#include "Engine/Core.h"
#include "Common.h"

class ENGINE_API LevelMap
{
public:
	static TileMap LoadLevelMap(char* FilePath);
	static void SaveTileMap(TileMap Map, std::string Address);
	int getWidth() { return mWidth; };
	int getHeight() { return mHeight; };
private:
	int mWidth;
	int mHeight;
};

