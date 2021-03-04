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

	SaveTileMap(tilemap);

	return tilemap;
}

void LevelMap::SaveTileMap(TileMap Map)
{
	//------------------------------------------------------------------------
	//Test for saving to XML file
	TiXmlDocument TestDoc;
	TiXmlDeclaration* Boo = new TiXmlDeclaration("1.0", "", "");
	TestDoc.LinkEndChild(Boo);
	TiXmlElement* TestRoot = new TiXmlElement("map");
	TestRoot->SetAttribute("version", "1.0");
	TestRoot->SetAttribute("width", Map[0].size());
	TestRoot->SetAttribute("height", Map.size());
	TestRoot->SetAttribute("tilewidth", "32");
	TestRoot->SetAttribute("tileheight", "32");

	TiXmlElement* TestElement = new TiXmlElement("tilemap");
	TestElement->SetAttribute("id", "tilemap");
	TestRoot->LinkEndChild(TestElement);

	for (int i = 0; i < atoi(TestRoot->Attribute("height")); i++)
	{
		for (int j = 0; j < atoi(TestRoot->Attribute("width")); j++)
		{
			TiXmlElement* TestTile = new TiXmlElement("tile");
			TestTile->SetAttribute("id", Map[i][j]);
			TestElement->LinkEndChild(TestTile);
		}
		
	}

	
	TestDoc.LinkEndChild(TestRoot);
	if (!TestDoc.SaveFile("TinyXML/XML_SaveTest.xml"));
	{
		cerr << TestDoc.ErrorDesc() << endl;
	}
	//------------------------------------------------------------------------
}
