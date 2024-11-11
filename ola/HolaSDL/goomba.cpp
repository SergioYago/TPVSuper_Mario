#include "goomba.h"
#include "Game.h"
#include <sstream>


goomba::goomba(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> mapPos.x >> mapPos.y;
	direccion = -1;
	mapPos.x = mapPos.x * 32;
	texture = game->getTexture(Game::TextureName::GOOMBA);
	screenPos.x = mapPos.x - g->getMapOffset();
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

// render del goomba en la pantalla 
void goomba::render()
{

	//SDL_Rect dest = { position.x * game->TILE_SIDE, position.y * game->TILE_SIDE, game->TILE_SIDE, game->TILE_SIDE };

	// si la posicion del goomba map offset y map offset mas la anchura de la pantalla, lo renderiza
	if (mapPos.x >= game->getMapOffset() && mapPos.x <= game->getMapOffset() + game->WIN_WIDTH)
	{
		screenPos.x = mapPos.x - game->getMapOffset();
		screenPos.y = mapPos.y;
	}
	else
	{
		screenPos.x = -100;
	}



	SDL_Rect destRect;
	destRect.x = screenPos.x * 32;
	destRect.y = screenPos.y *30;
	destRect.w = 32;
	destRect.h = 32;


	texture->renderFrame(destRect,0,0);

}


