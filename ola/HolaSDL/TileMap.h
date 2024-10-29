#pragma once
#include <SDL.h>
#include "vector2D.h"
#include "Texture.h"

#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class Game;
class TileMap
{
private: 
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;
	const int TILE_MAP=9;
	Game* game;

public:

	TileMap(const string& filename, Game* g) ;

	// Carga el mapa de teselas desde un archivo CSV y lo guarda en indices (atributo de TileMap) 
 	void LoadMap(const string& filename)
 	{
		ifstream file(filename);
	string line;
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 211; ++j) {
			getline(file, line, ',');
			indices[i][j] = stoi(line);
			cout << line<<" ";
		}
		cout << '\n';
	}
 	}
	void renderTileMap();

};

