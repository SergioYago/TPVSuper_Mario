﻿#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(const string& filename, Game g)
{
	
	vector<vector<int>> indices [Game::WIN_HEIGHT][211];
	background = g.getTexture(g.BACKGROUND);
	LoadMap(filename);
}

void TileMap ::  renderTileMap()
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
	for (int i = 0; i < g.WIN_WIDTH + 1; ++i) {
		for (int j = 0; j < g.WIN_HEIGHT; ++j) {
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