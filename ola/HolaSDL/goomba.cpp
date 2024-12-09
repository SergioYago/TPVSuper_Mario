#include "goomba.h"
#include "PlayState.h"
#include <sstream>

goomba::goomba(PlayState* g, Point2D pos, int w, int h, bool p, int points) : Enemy(g, pos, w, h, p, points)
{
	game = g;
	texture = g->getTexture(PlayState::TextureName::GOOMBA);
	position.x = pos.x * 32;
	position.y = pos.y * 32;
	colision = { position.x, position.y-64, w, h };
	velocity.x = 1;

}
/*
goomba::goomba(std::istream& is, PlayState* g) : Enemy(g)
{
	std::string filename;
	is >> filename;
	texture = PlayState->getTexture(PlayState:: TextureName:: GOOMBA);
	is >> position.x;
	is >> position.y;
	colision.x = position.x;
	colision.y = position.y;
	is >> velocity.x;
}
*/

void goomba::update()
{

	Collision aux;
	mueveY();

	aux = game->CheckColision(colision, Collision::ENEMIES);
	if (aux.vertical != 0)
	{
		aux.vertical = 0;
		igualaY(aux.vertical);
	}
	else
	{
		VueltaY();
	}
	mueveX();
	aux = game->CheckColision(colision, Collision::ENEMIES);
	if (aux.horizontal != 0)
	{
			ChangeDirection();
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
	
	if (colision.y < game->WIN_HEIGHT-32) 
	{  
		colision.y += 8;
		if (colision.y >= game->WIN_HEIGHT - 32) { 
			//SetisActive(false); 

		}
	}
	
}
void goomba::mueveX()
{
	if (velocity.x>=1)
	{
		
			if ((colision.x+32)>(200*32))
			{
				ChangeDirection();
			}
			colision.x += velocity.x;

			position.x += velocity.x;
		
	}
	else
	{
		if ((colision.x-32)<0)
		{
			ChangeDirection();
		}
		else {
			colision.x += velocity.x;

			position.x += velocity.x;
		}
	}
}
void goomba::igualaY(int i)
{
	position.y += i;
	colision.y = position.y;
}
void goomba::igualaX(int i)
{
	position.x += i;
	colision.x = position.x;
}
void goomba::VueltaY()
{
	position.y = colision.y;
}
void goomba::VueltaX()
{

}
void goomba::ChangeDirection()
{
	velocity.x = -velocity.x;
}


