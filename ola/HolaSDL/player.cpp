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
	textureB = game->getTexture(Game::PLAYERB);
	screenPosition.x = screenPosition.x * 32;
	direccion = 0;
	aspecto = 0;
	screenPosition.y=screenPosition.y*29;
	mapPosition = screenPosition;
	nextposition.x = screenPosition.x ;
	nextposition.y = screenPosition.y ;
	iniPos = mapPosition;
	nextposition.w = game->TILE_SIDE;
	nextposition.h = game->TILE_SIDE;
	vidas = 3;
	isGrounded = false;
	jump = 0;
	anim = 2;
	isBig = false;
	isInvinible = false;
	startTime = 0;
	ticksToWait = 4000;
}

void player::hit()
{
	SDL_Rect aux=nextposition;
	
	
	//SDL_GetRectIntersection();
	
	//si por encima, destruye al otro
	//si por debajo, vida--;
	
}

// Se encarga de actualizar la posición del jugador en función de las teclas pulsadas, cambiando la dirección del jugador.
// Además, si colisiona con un enemigo, llama a hit(); si colisiona con una moneda, incrementa monedas; si colisiona con una seta, incrementa aspecto.
void player::update()
{
	int mapoffset = game->getMapOffset();
	mueveY();
	if (nextposition.y+nextposition.h > game->WIN_HEIGHT - 26) { fell(); }
	else if(!game->checkMapColision(nextposition, hitted) && !game->checkBlockColision(nextposition, true))
	{
		igualaMovimientoy(); isGrounded = true;
	}
	else
	{
		VueltaPosiciony();
		isGrounded = false;
	}
	game->checkEnemyColision();
	game->checkMushColision();
	mueveX();
	 if (!game->checkMapColision(nextposition, hitted) && !game->checkBlockColision(nextposition, true))
	{
		igualaMovimiento(); 
	}
	else
	{
		VueltaPosicionx();
	}
	game->checkMushColision();
	game->checkEnemyColision();
	if(isInvinible&& SDL_GetTicks()-startTime>=ticksToWait	)
	{
		isInvinible = false;
	}
	if (mapPosition.x > 6300) { game->win(); }
}

//renderiza al jugador en la pantalla
void player::render()
{
	
	SDL_Rect destRect;
	destRect.x = screenPosition.x;
	destRect.y = screenPosition.y;
	destRect.h = nextposition.h;
	destRect.w = nextposition.w;

	
	//SDL_RenderCopy(game->getRenderer(), texture->getTexture(), nullptr, &destRect);
	if (!isBig) 
	{
		if (direccion == 0) {
			texture->renderFrame(destRect, 0, 0);
		}
		else if(direccion==1) {

			if (anim < 4) { anim++; }
			else if (anim == 4) { anim = 2; }
			texture->renderFrame(destRect, 0, anim);
		}
	else {
		if (anim < 4) { anim++; }
		else if (anim == 4) { anim = 2; }
		texture->renderFrame(destRect, 0, anim, SDL_FLIP_HORIZONTAL);

	}
	}
	else {
		if (direccion == 0) {
			textureB->renderFrame(destRect, 0, 0);
		}
		else if (direccion==1)  {

			if (anim < 4) { anim++; }
			else if (anim == 4) { anim = 2; }
			textureB->renderFrame(destRect, 0, anim);
		}
		else{
			if (anim < 4) { anim++; }
			else if (anim == 4) { anim = 2; }
			textureB->renderFrame(destRect, 0, anim,SDL_FLIP_HORIZONTAL);
		
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
				jump = 32;
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
void player::igualaMovimiento()
{
	float mapoffset = game->getMapOffset();
	if (direccion == 1 && screenPosition.x < game->WIN_WIDTH/2)
	{
		screenPosition.x += speed;
		 mapPosition.x = nextposition.x ;
	}
	else if (direccion == -1 && screenPosition.x > 0)
	{
		screenPosition.x -= speed;
		mapPosition.x = nextposition.x ;
	}

	// Si el jugador llega a la mitad de la pantalla e intenta avanzar, incrementa el mapOffset porque se incrementa la posición del jugador en el mapa, pero la posición en pantalla no cambia
	if (screenPosition.x >= game->WIN_WIDTH/2 && direccion == 1)
	{
		mapPosition.x=nextposition.x;
	}
	
}
void player::VueltaPosicionx()
{
	nextposition.x= mapPosition.x;
}
void player::VueltaPosiciony()
{
	nextposition.y= mapPosition.y;
	jump = 0;
}
void player::looseLive()
{
	if (isBig) 
	{ isBig = false; 
	nextposition.y =mapPosition.y=screenPosition.y= nextposition.y + 8;
	nextposition.h -= 8;
	isInvinible = true;
	startTime = SDL_GetTicks();
	}
	else if(!isInvinible) {
		vidas--; resetPos();
		game->resetMapOffset();
		if (vidas < 1) { game->loose(); }
	}
}

void player::fell()
{
	if (isBig)
	{
		isBig = false;
		nextposition.y = mapPosition.y = screenPosition.y = nextposition.y + 8;
		nextposition.h -= 8;
	}
	vidas--; resetPos();
	game->resetMapOffset();
	if (vidas < 1) { game->loose(); }
}

void player::lvlUp()
{
	if (!isBig) {
		isBig = true;
		nextposition.y = mapPosition.y = screenPosition.y = nextposition.y - 8;
		nextposition.h += 8;
	}
}

void player::mueveX()
{
	//de alguna manera no se mueve lo necesario para que llegue al abujero
	if (direccion == 1 && screenPosition.x < game->WIN_WIDTH )
	{
		nextposition.x+=speed;


	}
	else if (direccion == -1 && screenPosition.x > 0)
	{
		nextposition.x-=speed;


	}

}
	void player::mueveY()
	{
		// si no está en el suelo y ya ha llegado a la altura maxima del salto, empieza a caer
		if (!isGrounded && jump == 0)
		{
			nextposition.y += 4;
		}
		// si está en el suelo y se pulsa la tecla de salto, salta
		else if (isGrounded && jump >= 1)
		{
			nextposition.y -= 4;
			isGrounded = false;
			jump--;
		}
		// si no está en el suelo y no ha llegado a la altura maxima del salto, sigue subiendo
		else if (!isGrounded && jump > 0)
		{
			nextposition.y -= 4;
			jump--;
		}
		
	}
	void player::igualaMovimientoy()
	{
		mapPosition.y = screenPosition.y = nextposition.y;
	}
