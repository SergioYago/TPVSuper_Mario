#include "player.h"
#include "Game.h"

/*player::player(Texture* texture, Vector2D<int> position, Game* g)
	:game(g)
	, texture(g->getTexture(Game::PLAYER))
{
	game = g;

}
*/

//constructor de player, recibe un std::istream y un puntero a Game, con el que inicializa el atributo game. Lee de is la posici�n del jugador y sus vidas y las almacena en el atributo position y vidas. Inicializa el atributo texture con la textura del jugador.
player::player(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> screenPosition.x >> screenPosition.y >> vidas;
	texture = game->getTexture(Game::PLAYER);
	direccion = 0;
	aspecto = 0;
	screenPosition.y--;
	mapPosition = screenPosition;
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
void player::update()
{
	//si colisiona con un enemigo, hit();
	vidas--;
	aspecto--;
	
	//si colisiona con una moneda, monedas++;
	//si colisiona con una seta, aspecto++;
	aspecto++;

	// actualiza la posici�n del jugador en funci�n de las teclas pulsadas, cambiando la direccion del jugador


}
void player::render()
{

	SDL_Rect destRect;
	destRect.x = screenPosition.x* game->TILE_SIDE;
	destRect.y = screenPosition.y* game->TILE_SIDE;
	destRect.w = game->TILE_SIDE;
	destRect.h = game->TILE_SIDE;
	//SDL_RenderCopy(game->getRenderer(), texture->getTexture(), nullptr, &destRect);

	texture->render(destRect, 1, 0);


}