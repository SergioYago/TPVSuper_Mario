#pragma once
#include <SDL.h>
#include<SDL_rect.h>
#include "Vector2D.h"
#include "Texture.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class Game;
class TileMap
{
private: 
	Game* game;
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;
	const int TILE_MAP=211*32;
	//vector<vector<SDL_Rect>> colisions;
	
	

public:

	TileMap(const string& filename, Game* g) ;

	// Carga el mapa de teselas desde un archivo CSV y lo guarda en indices (atributo de TileMap) 
 	
	void renderTileMap();
	bool checkMapColision(const SDL_Rect& rect, bool fromPlayer);
};

