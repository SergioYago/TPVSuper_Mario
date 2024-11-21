#include "koopa.h"
#include "Game.h"
#include <sstream>


koopa::koopa(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> position.x >> position.y;
	velocity.x = -1;

	position.x = position.x * 32;
	position.y = (position.y - 1) * 32;
	texture = game->getTexture(Game::TextureName::GOOMBA);

	nextposition.x = position.x;
	nextposition.y = position.y;
	nextposition.w = nextposition.h = 32;
	
}
void koopa::update()
{
	mueveY();
	if(game->checkBlockColision('k',nextposition)||game->checkMapColision(nextposition)||game->checkGoombaCollision(nextposition))
	{
		igualaY();
	}
	else
	{
		VueltaY();
	}
	mueveX();
	if(game->checkBlockColision('k',nextposition)||game->checkGoombaCollision(nextposition)||game->checkMapColision(nextposition))
	{
		ChangeDirection();
		igualaX();
	}
	else
	{
		VueltaX();
	}
}

void koopa::hit()
{

}

// render del goomba en la pantalla 
void koopa::render()
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
		if (nextposition.y >= game->WIN_HEIGHT - 32) { SetisActive(false); }
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
void koopa::igualaY()
{
	nextposition.y = position.y;
}
void koopa::igualaX()
{
	nextposition.x = position.x;
}
void koopa::VueltaY()
{
	position.y = nextposition.y;
}
void koopa::VueltaX()
{

}
void koopa::ChangeDirection()
{
	velocity.x=-velocity.x;
}


