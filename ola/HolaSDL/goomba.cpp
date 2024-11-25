#include "goomba.h"
#include "Game.h"
#include <sstream>

goomba::goomba(Game* g, Point2D pos, int w, int h, bool p, int points) : Enemy(g, pos, w, h, p, points)
{
	texture = game->getTexture(Game::TextureName::GOOMBA);
	position.x = pos.x * 32;
	position.y = pos.y * 32;
	nextposition = { pos.x, pos.y, w, h };
	velocity.x = 1;

}
/*
goomba::goomba(std::istream& is, Game* g) : Enemy(g)
{
	std::string filename;
	is >> filename;
	texture = game->getTexture(Game:: TextureName:: GOOMBA);
	is >> position.x;
	is >> position.y;
	nextposition.x = position.x;
	nextposition.y = position.y;
	is >> velocity.x;
}
*/

void goomba::update()
{

	Collision aux;
	mueveY();

	aux = game->CheckColision(nextposition, Collision::ENEMIES);
	if (aux.vertical != 0)
	{
		igualaY(aux.vertical);
	}
	else
	{
		VueltaY();
	}
	mueveX();
	aux = game->CheckColision(nextposition, Collision::ENEMIES);
	if (aux.horizontal != 0)
	{
		igualaX(aux.vertical);
	}
	else
	{
		VueltaX();
	}
}


// render del goomba en la pantalla 
void goomba::render() const
{
	float mapoffset = game->getMapOffset();
	SDL_Rect destRect;
	destRect.x = position.x;// *32;
	destRect.y = position.y;// *32;
	destRect.w = width;
	destRect.h = height;

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
		if (nextposition.y >= game->WIN_HEIGHT - 32) { 
			//SetisActive(false); 

		}
	}
	
}
void goomba::mueveX()
{
	if (velocity.x>=1)
	{
		
			if ((nextposition.x+32)>(200*32))
			{
				ChangeDirection();
			}
			nextposition.x += velocity.x;

			position.x += velocity.x;
		
	}
	else
	{
		if ((nextposition.x-32)<0)
		{
			ChangeDirection();
		}
		else {
			nextposition.x -= velocity.x;

			position.x -= velocity.x;
		}
	}
}
void goomba::igualaY(int i)
{
	position.y += i;
	nextposition.y = position.y;
}
void goomba::igualaX(int i)
{
	position.x += i;
	nextposition.x = position.x;
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
	velocity.x = -velocity.x;
}


