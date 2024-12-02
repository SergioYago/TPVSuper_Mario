#include "koopa.h"
#include "Game.h"
#include <sstream>


koopa::koopa(Game* g, std::istream& is) : Enemy(g,is)
{
	texture = game->getTexture(Game::TextureName::KOOPA);

	nextposition = { position.x, position.y, g->TILE_SIDE, g->TILE_SIDE };
}


void koopa::update()
{
	Collision aux;
	mueveY();
	
	aux = game->CheckColision(nextposition,Collision::ENEMIES);
	if(aux.vertical!=0)
	{
		igualaY(aux.vertical);
	}
	else
	{
		VueltaY();
	}
	/*mueveX();
	aux = game->CheckColision(nextposition, Collision::ENEMIES);
	if (aux.horizontal != 0)
	{
		igualaX(aux.vertical);
	}
	else
	{
		VueltaX();
	}*/
}



// render del goomba en la pantalla 
void koopa::render() const
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
void koopa::mueveY()
{

	if (nextposition.y < game->WIN_HEIGHT - 32)
	{
		nextposition.y += 8;
		if (nextposition.y >= game->WIN_HEIGHT - 32) { //SetisActive(false); }
		}

	}
}
void koopa::mueveX()
{
	if (velocity.x == 1)
	{

		if ((nextposition.x + 32) > (200 * 32))
		{
			ChangeDirection();
		}
		nextposition.x += 2;

		position.x += 2;

	}
	else
	{
		if ((nextposition.x - 32) < 0)
		{
			ChangeDirection();
		}
		else {
			nextposition.x -= 2;

			position.x -= 2;
		}
	}
}
void koopa::igualaY(int i)
{
	nextposition.y = position.y+i;
	position.y += i;
}
void koopa::igualaX(int i )
{
	
	nextposition.x = position.x+i;
	position.x += i;
}
void koopa::VueltaY()
{
	position.y = nextposition.y;
}
void koopa::VueltaX()
{
	position.x = nextposition.x;
}
void koopa::ChangeDirection()
{
	velocity.x=-velocity.x;
}


