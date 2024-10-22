#pragma once
#include <SDL.h>
#include <vector>
#include "Texture.h"
#include "Game.h"
#include <fstream>
#include <string>
using namespace std;
class TileMap
{
private: 
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;
	const int TILE_MAP;

public:

	TileMap();

	void Lee() {
		string h;
		ifstream in("../assets/maps/world1.csv");
		cin >> h;
		cout << h;
	}

	int renderTileMap()
	{
		
		Game g;

		int mapOffset;  // atributo de Game

		// Primera columna de la matriz del mapa visible en la ventana
		int x0 = mapOffset / TILE_MAP;
		// Anchura oculta de esa primera columna
		int d0 = mapOffset % TILE_MAP;

		// Recuadro donde se pintará la tesela en la ventana
		SDL_Rect rect;
		rect.w = g.TILE_SIDE;
		rect.h = g.TILE_SIDE;

		// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
		for (int i = 0; i < g.WINDOW_WIDTH + 1; ++i) {
			for (int j = 0; j < g.WINDOW_HEIGHT; ++j) {
				// Índice en el conjunto de patrones de la matriz de índices
				int indice = indices[x0 + i][j];

				// Separa número de fila y de columna
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

