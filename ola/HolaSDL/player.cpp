
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
	peque = game->getTexture(Game::PLAYER);
	grandote = game->getTexture(Game::GRANDE);
	direccion = 0;
	aspecto = 0;
	screenPosition.y=6;
	mapPosition = screenPosition;
	nextposition.x = screenPosition.x*game->TILE_SIDE ;
	nextposition.y = screenPosition.y*game->TILE_SIDE ;
	nextposition.w = game->TILE_SIDE;
	nextposition.h = game->TILE_SIDE;

	isGrounded = false;
	jump = 0;
	anim = 2;
	
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
	Collision aux;
	mueveY();

	aux = game->CheckColision(nextposition, Collision::PLAYER);
	if (aux.vertical != 0)
	{
		if (aux.vertical == aux.horizontal && aux.vertical == -100)
		{
			if (jump == 0)
			{
				aux.vertical = ((nextposition.y / 32) + 1) * 32 - nextposition.y;
				isGrounded = true;
			}
			else
			{
				aux.vertical = ((nextposition.y / 32) - 1) - nextposition.y;
				jump = 0;
			}
			
		}
		igualaMovimientoy(aux.vertical);
	}
	 
	else
	{
		VueltaPosiciony();
	}
	mueveX();
	aux = game->CheckColision(nextposition, Collision::PLAYER);
	if (aux.horizontal != 0)
	{	
		if(aux.horizontal==aux.vertical&&aux.horizontal==-100)
		{
		if (direccion==1)
		{
			aux.horizontal = -(nextposition.x + 30 - nextposition.x)/32;
			
		}
		else
		{
			aux.horizontal = (nextposition.x -30 - nextposition.x)/32;
		}
		}
		igualaMovimiento(aux.horizontal);
	}
	else
	{
		VueltaPosicionx();
	}
	
	//si colisiona con un enemigo, hit();
	//si colisiona con una moneda, monedas++;
	//si colisiona con una seta, aspecto++;

	// actualiza la posición del jugador en función de las teclas pulsadas, cambiando la direccion del jugador


	// Si el jugador llega a la mitad de la pantalla e intenta avanzar, incrementa el mapOffset porque se incrementa la posición del jugador en el mapa, pero la posición en pantalla no cambia
	

}

//renderiza al jugador en la pantalla
void player::render()
{
	
	SDL_Rect destRect;
	destRect.x = screenPosition.x* game->TILE_SIDE;
	
	destRect.w = 32;
	
	
	//SDL_RenderCopy(game->getRenderer(), texture->getTexture(), nullptr, &destRect);
	if (aspecto == 0) {
		destRect.h = 32;
		destRect.y = screenPosition.y * game->TILE_SIDE;
		if (!isGrounded) {
			peque->renderFrame(destRect, 0, 6);
		}
		else if (direccion == 0) {
			peque->renderFrame(destRect, 0, 0);
		}
		else {

			if (anim < 4) { anim++; }
			else if (anim == 4) { anim = 2; }
			peque->renderFrame(destRect, 0, anim);
		}
	}
	else if (aspecto == 1) {
		destRect.h = 64;
		destRect.y = (screenPosition.y-1) * game->TILE_SIDE;
		if (!isGrounded) {
			grandote->renderFrame(destRect, 0, 6);
		}
		else if (direccion == 0) {
			grandote->renderFrame(destRect, 0, 0);
		}
		else {

			if (anim < 4) { anim++; }
			else if (anim == 4) { anim = 2; }
			grandote->renderFrame(destRect, 0, anim);
		}
	}

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
		
		case SDLK_SPACE:
			if (isGrounded)
			{
				jump = 16;
				isGrounded = false;
			}

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
void player::igualaMovimiento(int i)
{
	mapPosition.x += i;
	screenPosition.x +=i;
	nextposition.x = mapPosition.x*32;
	
}
void player::VueltaPosicionx()
{
	float mapoffset = game->getMapOffset();
	if (direccion == 1 && screenPosition.x < game->WIN_WIDTH / 64)
	{

		screenPosition.x++; ;
		mapPosition.x = nextposition.x / 32;
	}
	else if (direccion == -1 && screenPosition.x > 0)
	{

		screenPosition.x--;
		mapPosition.x = nextposition.x / 32;
	}

	// Si el jugador llega a la mitad de la pantalla e intenta avanzar, incrementa el mapOffset porque se incrementa la posición del jugador en el mapa, pero la posición en pantalla no cambia
	else if (screenPosition.x == game->WIN_WIDTH / 64 && direccion == 1)
	{
		mapPosition.x = nextposition.x / 32;
	}
	
}
void player::VueltaPosiciony()
{
	mapPosition.y = screenPosition.y = nextposition.y / 32;
	isGrounded = false;
	
}
void player::mueveX()
{

	//de alguna manera no se mueve lo necesario para que llegue al abujero
	if (direccion == 1 && screenPosition.x < game->WIN_WIDTH / 64)
	{
		nextposition.x+=32;


	}
	else if (direccion == -1 && screenPosition.x > 0)
	{
		nextposition.x-=32;


	}
	else if (screenPosition.x == game->WIN_WIDTH / 64 && direccion == 1)
	{
		nextposition.x+=32;


	}
}
	void player::mueveY()
	{
		// si no está en el suelo y ya ha llegado a la altura maxima del salto, empieza a caer
		if (!isGrounded && jump == 0)
		{
			nextposition.y += 8;
		}
		// si está en el suelo y se pulsa la tecla de salto, salta
		else if (isGrounded && jump >= 1)
		{
			nextposition.y -= 8;
			isGrounded = false;
			jump--;
		}
		// si no está en el suelo y no ha llegado a la altura maxima del salto, sigue subiendo
		else if (!isGrounded && jump > 0)
		{
			nextposition.y -= 8;
			jump--;
		}
		else { nextposition.y += 8; }
		
	}
	void player::igualaMovimientoy(int i)
	{
		mapPosition.y += i/32;
		screenPosition.y = mapPosition.y;
		nextposition.y = mapPosition.y*32;
		
	}
