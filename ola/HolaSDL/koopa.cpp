#include "koopa.h"
#include "Game.h"
#include <sstream>


Koopa::Koopa(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> mapPos.x >> mapPos.y;
	direccion = -1;
	mapPos.x = mapPos.x * 32;
	mapPos.y = mapPos.y * 29;
	texture = game->getTexture(Game::TextureName::KOOPA);
	screenPos.x = mapPos.x - g->getMapOffset();
	screenPos.y = mapPos.y;
	nextposition.x = mapPos.x;
	nextposition.y = mapPos.y;
	nextposition.w = nextposition.h = 32;
}

void Koopa::hit()
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

// render del Koopa en la pantalla 
void Koopa::render()
{
	float mapoffset = game->getMapOffset();
	//SDL_Rect dest = { position.x * game->TILE_SIDE, position.y * game->TILE_SIDE, game->TILE_SIDE, game->TILE_SIDE };

	// si la posicion del Koopa map offset y map offset mas la anchura de la pantalla, lo renderiza
	if (mapPos.x >= mapoffset && mapPos.x <= mapoffset + game->WIN_WIDTH)
	{
		screenPos.x = (mapPos.x - mapoffset);
		screenPos.y = mapPos.y;
	}
	



	SDL_Rect destRect;
	destRect.x = screenPos.x;
	destRect.y = screenPos.y;
	destRect.w = 32;
	destRect.h = 32;


	texture->renderFrame(destRect,0,0);

}
void Koopa::update()
{
}
void Koopa::mueveY()
{
	nextposition.y+=4;
	//if (nextposition.y > game->WIN_HEIGHT) {  nextposition.y -= 8; }
}
void Koopa::mueveX()
{

	if ((nextposition.x + 32 * direccion) > (200 * 32)|| (nextposition.x + 32 * direccion) <0)
	{
		ChangeDirection();
	}
	else {
		nextposition.x += 4 * direccion;
		mapPos.x += 4 * direccion;
		screenPos.x += 4 * direccion;
	}
	
}
void Koopa::igualaY()
{
	mapPos.y = screenPos.y = nextposition.y;
}
void Koopa::igualaX()
{
	mapPos.x = nextposition.x; 
	screenPos.x = mapPos.x - game->getMapOffset();
}
void Koopa::VueltaY()
{
	nextposition.y = mapPos.y;
}
void Koopa::VueltaX()
{
	nextposition.x = mapPos.x;
	ChangeDirection();
}
void Koopa::ChangeDirection()
{
	direccion = -direccion;
}


