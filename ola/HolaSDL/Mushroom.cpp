#include "Mushroom.h"
#include "Game.h"
#include <sstream>


Mushroom::Mushroom(Point2D pos, Game* g)
	:game(g)
{
	game = g;
	mapPos.x = pos.x;
	mapPos.y = pos.y;
	direccion = 1;
	texture = game->getTexture(Game::TextureName::MUSHROOM);
	screenPos.x = mapPos.x - g->getMapOffset();
	screenPos.y = mapPos.y;
	nextposition.x = mapPos.x;
	nextposition.y = mapPos.y;
	nextposition.w = nextposition.h = 32;

}

Mushroom::~Mushroom()
{
	game = nullptr;
	texture = nullptr;
}

void Mushroom::hit()
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

// render del Mushroom en la pantalla 
void Mushroom::render()
{
	float mapoffset = game->getMapOffset();
	//SDL_Rect dest = { position.x * game->TILE_SIDE, position.y * game->TILE_SIDE, game->TILE_SIDE, game->TILE_SIDE };

	// si la posicion del Mushroom map offset y map offset mas la anchura de la pantalla, lo renderiza
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
void Mushroom::update()
{
	mueveY();
	if (nextposition.y+nextposition.h > game->WIN_HEIGHT - 26)
	{
		game->destroyMush(this);
	}
	else if (!game->checkMapColision(nextposition, false) && !game->checkBlockColision(nextposition, false))
	{
		igualaY();
	}
	else
	{
		VueltaY();

	}
	mueveX();
	if (!game->checkMapColision(nextposition, false) && !game->checkBlockColision(nextposition, false))
	{
		igualaX();
	}
	else
	{
		VueltaX();

	}

}
void Mushroom::mueveY()
{
	nextposition.y+=4;
	//if (nextposition.y > game->WIN_HEIGHT) {  nextposition.y -= 8; }
}
void Mushroom::mueveX()
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
void Mushroom::igualaY()
{
	mapPos.y = screenPos.y = nextposition.y;
}
void Mushroom::igualaX()
{
	mapPos.x = nextposition.x; 
	screenPos.x = mapPos.x - game->getMapOffset();
}
void Mushroom::VueltaY()
{
	nextposition.y = mapPos.y;
}
void Mushroom::VueltaX()
{
	nextposition.x = mapPos.x;
	ChangeDirection();
}
void Mushroom::ChangeDirection()
{
	direccion = -direccion;
}


