#include "goomba.h"
#include "Game.h"
#include <sstream>


goomba::goomba(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> position.x >> position.y;
	direccion = -1;

	position.x = position.x * 32;
	position.y = (position.y-1) * 32;
	texture = game->getTexture(Game::TextureName::GOOMBA);

	nextposition.x = position.x;
	nextposition.y = position.y;
	nextposition.w = nextposition.h = 32;
	isactive = true;
}

void goomba::hit()
{

}
void goomba::update()
{

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
	if (direccion == -1) {  }
	else {   }
}
void goomba::VueltaY()
{
	position.y = nextposition.y;
}
void goomba::VueltaX()
{

}
void goomba::ChangeDirection()
{
	direccion = -direccion;
}


