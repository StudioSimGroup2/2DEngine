#include "LevelMap.h"

#include <vector>
#include <iostream>
#include <istream>

TileMap LevelMap::LoadLevelMap(const std::string& FilePath)
{
	TileMap tilemap;

	//Get the whole xml document.
	TiXmlDocument doc;
	if (!doc.LoadFile(FilePath.c_str()))
	{
		std::cerr << doc.ErrorDesc() << std::endl;
	}

	//Now get the root element.
	TiXmlElement* root = doc.FirstChildElement();
	if (!root)
	{
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
	}
	else
	{
		//We have the root - Get the dimensions and convert to integers.
		int width = atoi(root->Attribute("width"));
		int height = atoi(root->Attribute("height"));
		int w = 0, h = 0;
		TiXmlElement* HELP = root->FirstChildElement();
		std::vector<int> Row;
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

void LevelMap::SaveTileMap(TileMap Map, std::string Address)
{
	int MaxHeight = Map.size();
	int MaxWidth = Map[0].size();
	for (int q = 1; q < MaxHeight; q++)
	{
		MaxWidth = std::max(int(Map[q].size()), MaxWidth);
	}
	//------------------------------------------------------------------------
	//Test for saving to XML file
	TiXmlDocument Doc;
	TiXmlDeclaration* Header = new TiXmlDeclaration("1.0", "", "");
	Doc.LinkEndChild(Header);
	TiXmlElement* Root = new TiXmlElement("map");
	Root->SetAttribute("version", "1.0");
	Root->SetAttribute("width", MaxWidth);
	Root->SetAttribute("height", MaxHeight);
	Root->SetAttribute("tilewidth", "32");
	Root->SetAttribute("tileheight", "32");

	TiXmlElement* TestElement = new TiXmlElement("tilemap");
	TestElement->SetAttribute("id", "tilemap");
	Root->LinkEndChild(TestElement);

	for (int i = 0; i < atoi(Root->Attribute("height")); i++)
	{
		for (int j = 0; j < atoi(Root->Attribute("width")); j++)
		{
			TiXmlElement* TestTile = new TiXmlElement("tile");
			if (j < Map[i].size())
			{
				TestTile->SetAttribute("id", Map[i][j]);
			}
			else
			{
				TestTile->SetAttribute("id", 0);
			}
			TestElement->LinkEndChild(TestTile);
		}
		
	}

	
	Doc.LinkEndChild(Root);
	Doc.SaveFile(Address.c_str());
	if (!Doc.SaveFile(Address.c_str()))
	{
		std::string error = Doc.ErrorDesc();
		std::cerr << Doc.ErrorDesc() << std::endl;

	}
	//------------------------------------------------------------------------
}
