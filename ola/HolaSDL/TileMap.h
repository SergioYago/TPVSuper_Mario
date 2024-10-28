#pragma once
#include <SDL.h>
#include "vector2D.h"
#include "Texture.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class TileMap
{
private: 
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;
	const int TILE_MAP;

public:

	TileMap();

	// Carga el mapa de teselas desde un archivo CSV y lo guarda en indices (atributo de TileMap) 

	void loadMap(const string& filename) {
		ifstream file(filename);
		string line;
		for (int i = 0; i < Game::WINDOW_HEIGHT; ++i) {
			for (int j = 0; j < Game::WINDOW_WIDTH; ++j) {
				getline(file, line, ',');
				indices[i][j] = stoi(line);
			}
		}
	}

	int renderTileMap()
	{
		
		Game g;

		int mapOffset;  // atributo de Game

		// Primera columna de la matriz del mapa visible en la ventana
		int x0 = mapOffset / TILE_MAP;
		// Anchura oculta de esa primera columna
		int d0 = mapOffset % TILE_MAP;

		// Recuadro donde se pintar� la tesela en la ventana
		SDL_Rect rect;
		rect.w = g.TILE_SIDE;
		rect.h = g.TILE_SIDE;

		// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
		for (int i = 0; i < g.WINDOW_WIDTH + 1; ++i) {
			for (int j = 0; j < g.WINDOW_HEIGHT; ++j) {
				// �ndice en el conjunto de patrones de la matriz de �ndices
				int indice = indices[x0 + i][j];

				// Separa n�mero de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * g.TILE_SIDE;
				rect.y = j * g.TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				background->renderFrame(rect, fy, fx);
			}
		}
	}
};

