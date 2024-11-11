#include "player.h"
#include "Game.h"


//constructor de player, recibe un std::istream y un puntero a Game, con el que inicializa el atributo game. 
// Lee de is la posición del jugador y sus vidas y las almacena en el atributo position y vidas. 
// Inicializa el atributo texture con la textura del jugador.
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
	nextposition.x = screenPosition.x * game->TILE_SIDE;
	nextposition.y = screenPosition.y * game->TILE_SIDE;
	nextposition.w = game->TILE_SIDE;
	nextposition.h = game->TILE_SIDE;
	
}

void player::hit()
{
	SDL_Rect aux;
	aux.x = screenPosition.x * game->TILE_SIDE;
	aux.y = screenPosition.y * game->TILE_SIDE;
	aux.w = game->TILE_SIDE;
	aux.h = game->TILE_SIDE;
	//SDL_GetRectIntersection();
	
	//si por encima, destruye al otro
	//si por debajo, vida--;
	vidas--;
	if (vidas<1)
	{
		game->loose();
	}
}

// Se encarga de actualizar la posición del jugador en función de las teclas pulsadas, cambiando la dirección del jugador.
// Además, si colisiona con un enemigo, llama a hit(); si colisiona con una moneda, incrementa monedas; si colisiona con una seta, incrementa aspecto.
void player::update()
{
	
	int mapoffset = game->getMapOffset();

	//si colisiona con un enemigo, hit();
	//si colisiona con una moneda, monedas++;
	//si colisiona con una seta, aspecto++;

	// actualiza la posición del jugador en función de las teclas pulsadas, cambiando la direccion del jugador
	if (direccion == 1 && screenPosition.x < game->WIN_WIDTH/64)
	{
		nextposition.x+=0.3;

		
	}
	else if (direccion == -1 && screenPosition.x>0)
	{
		nextposition.x-=0.3;
	

	}
	if (screenPosition.x == game->WIN_WIDTH / 64 && direccion == 1)
	{
		nextposition.x+=0.3;
	

	}

	// Si el jugador llega a la mitad de la pantalla e intenta avanzar, incrementa el mapOffset porque se incrementa la posición del jugador en el mapa, pero la posición en pantalla no cambia
	

}

//renderiza al jugador en la pantalla
void player::render()
{

	SDL_Rect destRect;
	destRect.x = screenPosition.x* game->TILE_SIDE;
	destRect.y = screenPosition.y* game->TILE_SIDE;
	destRect.w = game->TILE_SIDE;
	destRect.h = game->TILE_SIDE;
	
	//SDL_RenderCopy(game->getRenderer(), texture->getTexture(), nullptr, &destRect);

	texture->renderFrame(destRect, 0, 0);


}


// gestiona los eventos de teclado. 
// Si se pulsa la tecla de flecha izquierda, la dirección del jugador se pone a -1. 
// Si se pulsa la tecla de flecha derecha, la dirección del jugador se pone a 1. 
// Tambien tiene en cuenta cuando se deja de pulsar una tecla, para que el jugador deje de moverse.

void player::handleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:

			break;
		case SDLK_DOWN:

			break;
		case SDLK_LEFT:
			direccion = -1;
			break;
		case SDLK_RIGHT:
			direccion = 1;
			break;
		}

		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			direccion = 0;
			break;
		case SDLK_RIGHT:
			direccion = 0;
			break;
		}
		break;
	}
}
void player::igualaMovimiento()
{
	if (direccion == 1 && screenPosition.x < game->WIN_WIDTH / 64)
	{
		
		screenPosition.x+=0.3;
		mapPosition.x+=0.3;
		cout << mapPosition.x;
	}
	else if (direccion == -1 && screenPosition.x > 0)
	{
		
		screenPosition.x-=0.3;
		mapPosition.x-=0.3;
	}

	// Si el jugador llega a la mitad de la pantalla e intenta avanzar, incrementa el mapOffset porque se incrementa la posición del jugador en el mapa, pero la posición en pantalla no cambia
	if (screenPosition.x == game->WIN_WIDTH / 64 && direccion == 1)
	{
		mapPosition.x+=0.3;
	}
}
void player::VueltaPosicion()
{
	nextposition.x = mapPosition.x;
	nextposition.y = mapPosition.y;
}
