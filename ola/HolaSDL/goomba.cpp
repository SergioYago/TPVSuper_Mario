#include "goomba.h"
#include "Game.h"
#include <sstream>


goomba::goomba(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> position.x >> position.y;
	direccion = -1;
	mapPos.x = mapPos.x * 32;
	position.x = position.x * 32;
	position.y = (position.y-1) * 32;
	texture = game->getTexture(Game::TextureName::GOOMBA);
	screenPos.x = mapPos.x - g->getMapOffset();
	nextposition.x = position.x;
	nextposition.y = position.y;
	nextposition.w = nextposition.h = 32;
	isactive = true;
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
	float mapoffset = game->getMapOffset();
	SDL_Rect destRect;
	destRect.x = position.x;// *32;
	destRect.y = position.y;// *32;
	destRect.w = 32;
	destRect.h = 32;

	if (position.x >= game->getMapOffset() && position.x <= game->getMapOffset() + game->WIN_WIDTH)
	{
		destRect.x = position.x - game->getMapOffset();
		texture->renderFrame(destRect, 0, 0);
	}




	// si la posicion del goomba map offset y map offset mas la anchura de la pantalla, lo renderiza
	/*
	if (mapPos.x >= mapoffset && mapPos.x <= mapoffset + game->WIN_WIDTH)
	{
		screenPos.x = (mapPos.x - mapoffset);
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
	*/
}
void goomba::mueveY()
{
	
	if (nextposition.y < game->WIN_HEIGHT-32) 
	{  
		nextposition.y += 8;
		if (nextposition.y >= game->WIN_HEIGHT - 32) { SetisActive(false); }
	}
	
}
void goomba::mueveX()
{
	if (direccion==1)
	{
		
			if ((nextposition.x+32)>(200*32))
			{
				ChangeDirection();
			}
			nextposition.x += 2;
			mapPos.x++;
			screenPos.x++;

			position.x += 2;
		
	}
	else
	{
		if ((nextposition.x-32)<0)
		{
			ChangeDirection();
		}
		else {
			nextposition.x -= 2;
			mapPos.x--;
			screenPos.x--;

			position.x -= 2;
		}
	}
}
void goomba::igualaY()
{
	nextposition.y = position.y;
}
void goomba::igualaX()
{
	if (direccion == -1) { mapPos.x = nextposition.x / 32; screenPos.x = mapPos.x - game->getMapOffset(); }
	else { mapPos.x = nextposition.x / 32;  }
}
void goomba::VueltaY()
{
	position.y = nextposition.y;
}
void goomba::VueltaX()
{
	nextposition.x = mapPos.x*32;
}
void goomba::ChangeDirection()
{
	direccion = -direccion;
}


