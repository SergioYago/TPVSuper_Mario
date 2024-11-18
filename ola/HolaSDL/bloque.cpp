#include "bloque.h"
#include "Game.h"
#include <sstream>

// constructor de bloque, recibe un istream y un puntero al juego y guarda la posición del bloque. 
// Si el tipo de bloque es ? es sorpresa y contiene un potenciador (P) o moneda (C). 
// Si el tipo de bloque es B es ladrillo y no contiene nada.
// Si el tipo de bloque es 0 es vacío y no contiene nada. 
// Si el tipo de bloque es H es oculto y contiene un potenciador o moneda.
bloque::bloque(std::istream& is, Game* g)
	:game(g)
{
	game = g;
	is >> position.x >> position.y;
	char tipoBl;
	is >> tipoBl;
	if (tipoBl == '?') {
		tipoBloque = sorpresa;
		char accionBl;
		is >> accionBl;
		if (accionBl == 'P') {
			accionBloque = potenciador;
		}
		else if (accionBloque == 'C') {
			accionBloque = moneda;
		}
	}
	else if (tipoBl == 'B') {
		tipoBloque = ladrillo;
		accionBloque = nada;
	}
	else if (tipoBl == '0') {
		tipoBloque = vacio;
		accionBloque = nada;
	}
	else if (tipoBl == 'H') {
		tipoBloque = oculto;
		char accionBl;
		is >> accionBl;
		if (accionBl == 'P') {
			accionBloque = potenciador;
		}
		else if (accionBl == 'C') {
			accionBloque = moneda;
		}
	}
	position.x = position.x * 32;
	position.y = position.y * 32;
	texture = game->getTexture(Game::BLOQUE);
	anim = 0;
}

// render del bloque en la pantalla
void bloque::render()
{
	SDL_Rect destRect;
	destRect.x = position.x;// *32;
	destRect.y = position.y;// *32;
	destRect.w = 32;
	destRect.h = 32;

	// se dibuja el bloque en la pantalla si su posición es mayor que el map offset y menor que el map offset más la anchura de la pantalla
	if (position.x >= game->getMapOffset() && position.x <= game->getMapOffset() + game->WIN_WIDTH)
	{
		destRect.x = position.x - game->getMapOffset();

		// se dibuja el bloque en función de su tipo y acción
		if (tipoBloque == ladrillo) {
			texture->renderFrame(destRect, 0, 5);
		}
		else if (tipoBloque == sorpresa) {
			if (anim < 3) { anim++; }
			else if (anim == 3) { anim = 0; }
			texture->renderFrame(destRect, 0, anim);
		}
		else if (tipoBloque == vacio) {
			texture->renderFrame(destRect, 0, 4);
		}

		//texture->renderFrame(destRect, 0, 0);
	}
}
