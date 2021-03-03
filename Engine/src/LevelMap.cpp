#include "LevelMap.h"


TileMap LevelMap::LoadLevelMap(char* FilePath)
{
	int tile;
	TileMap tilemap;
	ifstream InFile;
	InFile.open(FilePath);

	if (!InFile.good()) { cerr << "Can't open map file " << FilePath << endl; }

	else
	{
		int Height = 0, Width = 0;
		InFile >> Height; InFile >> Width;

		for (int i = 0; i < Height; i++)
		{
			vector<int> HELP2;
			for (int j = 0; j < Width; j++)
			{
				InFile >> tile;
				HELP2.push_back(tile);
			}
			tilemap.push_back(HELP2);
		}
	}
	return tilemap;
}