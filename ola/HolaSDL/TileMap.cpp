#include "TileMap.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include  <SDL_rect.h>
#include "PlayState.h"

TileMap::TileMap(const string& filename, PlayState* g)
	:game(g)
	,background(g->getTexture(PlayState::BACKGROUND))
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
	rows;
	file.close();
	file.open(filename);
	indices = vector<vector<int>>(rows, vector<int>(210, 0));
	//colisions = vector<vector<SDL_Rect>>(rows, vector<SDL_Rect>(210, 0));
	for(int i =0;i<rows;i++)
	{
		for(int j=0;j<210;j++)
		{
			getline(file, line, ',');
			indices[i][j] = stoi(line);
			
			
			

		}
		
	}
	

	
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
	for (int i = 0; i < 16; ++i) {
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

	}
}
bool TileMap::checkMapColision(const SDL_Rect& rect, bool fromPlayer)
{
	vector<vector<int>> matrix; // atributos de TileMap
	Texture* texture;

	constexpr int OBSTACLE_THRESHOLD = 4; // constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / PlayState::TILE_SIDE;
	int col0 = rect.x / PlayState::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / PlayState::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1)/ PlayState::TILE_SIDE;

	for (int row = row0; row <= row1; ++row)
		for (int col = col0; col <= col1; ++col) {
			int indice = indices[row][col];

			if (indice != -1 && indice % background->getNumColumns() < OBSTACLE_THRESHOLD)
			{
				return true;
			}
				
		}

	return false;
}