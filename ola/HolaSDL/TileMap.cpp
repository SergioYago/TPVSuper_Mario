#include "TileMap.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "Game.h"

TileMap::TileMap(const string& filename, Game* g)
	:game(g)
	,background(g->getTexture(Game::BACKGROUND))
{
	game = g;

	
	//background = g->getTexture(g->BACKGROUND);
	int rows = 0;
	ifstream file(filename);
	

	string line;
	while (getline(file, line))
	{
		rows++;
		
	}
	rows--;
	file.close();
	file.open(filename);
	indices = vector<vector<int>>(rows, vector<int>(210, 0));
	for(int i =0;i<rows;i++)
	{
		for(int j=0;j<210;j++)
		{
			getline(file, line, ',');
			indices[i][j] = stoi(line);
		}
	}
	/*vector<int> v[211];
	stringstream stream(line);
	int aux;
	while (stream >> aux)
	{
		v->push_back(aux);
		if (stream.peek() == ',') { stream.ignore(); }
	}*/
}

void TileMap ::  renderTileMap()
{

	
	
	int mapOffset = game->getMapOffset();  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / TILE_MAP;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % TILE_MAP;

	// Recuadro donde se pintar� la tesela en la ventana
	SDL_Rect rect;
	rect.w = game->TILE_SIDE;
	rect.h = game->TILE_SIDE;
	//SDL_Surface* background_surface = SDL_CreateRGBSurface(0, 16, 210, 0, 138, 132, 255, 255);
	
	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 210; ++j) {
			// indice en el conjunto de patrones de la matriz de indices
			int indice = indices[x0 + i][j];
			//cout << indice << " ";
			// Separa numero de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + j * game->TILE_SIDE;
			rect.y = i * game->TILE_SIDE;
			

			// Usa renderFrame para pintar la tesela
			background->renderFrame(rect, fy, fx);
		}
		//cout << '\n';
	}
}