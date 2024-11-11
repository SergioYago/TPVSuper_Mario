#include "goomba.h"
#include "Game.h"
#include <sstream>


goomba::goomba(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> position.x >> position.y;
	direccion = -1;
	texture = game->getTexture(Game::TextureName::PLAYER);
}

void goomba::hit()
{
	//SDL_Rect aux;
	//aux.x = position.x * game->TILE_SIDE;
	//aux.y = position.y * game->TILE_SIDE;
	//aux.w = game->TILE_SIDE;
	//aux.h = game->TILE_SIDE;
	//SDL_GetRectIntersection();

	//si por encima, destruye al otro
	//si por debajo, vida--;
	//vidas--;
	//if (vidas<1)
	//{
	//	game->loose();
	//}
}

