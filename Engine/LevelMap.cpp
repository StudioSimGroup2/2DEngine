#include "LevelMap.h"

TileMap LevelMap::LoadLevelMap(char* FilePath)
{
	int tile;
	TileMap tilemap;


	//Get the whole xml document.
	TiXmlDocument doc;
	if (!doc.LoadFile("TinyXML/XML_Test.xml"))
	{
		cerr << doc.ErrorDesc() << endl;
	}

	//Now get the root element.
	TiXmlElement* root = doc.FirstChildElement();
	if (!root)
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	}
	else
	{
		//We have the root - Get the dimensions and convert to integers.
		int width = atoi(root->Attribute("width"));
		int height = atoi(root->Attribute("height"));
		int w = 0, h = 0;
		vector<int> Row;
		for (TiXmlElement* tileElement = root->FirstChildElement("tilemap")->FirstChildElement("tile"); tileElement != NULL; tileElement = tileElement->NextSiblingElement())
		{
			//Populate this position in the array with the tile type.
			Row.push_back(atoi(tileElement->Attribute("id")));
			w++;
			if (w >= width)
			{
				tilemap.push_back(Row);
				Row.clear();
				w = 0;
			}
		}
	}



	//old code for loading in tile map
	/*ifstream InFile;
	InFile.open(FilePath);
	if (!InFile.good()) { cerr << "Can't open map file " << FilePath << endl; }

	else
	{
		int Height = 0, Width = 0;
		InFile >> Height; InFile >> Width;

		for (int i = 0; i < Height; i++)
		{
			vector<int> Row;
			for (int j = 0; j < Width; j++)
			{
				InFile >> tile;
				Row.push_back(tile);
			}
			tilemap.push_back(Row);
		}
	}*/


	return tilemap;
}
