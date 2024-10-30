#include "player.h"
#include "Game.h"
player::player(Texture* texture, Vector2D<int> position, Game* g)
	:game(g)
	, texture(g->getTexture(Game::PLAYER))
{
	vidas = 3;
	position.x = 32;
	position.y = 448;
}
void player::hit()
{
	//si por encima, destruye al otro
	//si por debajo, vida--;
	vidas--;
	if (vidas<1)
	{
		game->loose();
	}
}