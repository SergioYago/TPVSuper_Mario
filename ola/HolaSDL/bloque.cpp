#include "bloque.h"
#include "Game.h"
#include <sstream>

// constructor de bloque, recibe un istream y un puntero al juego y guarda la posición del bloque. 
// Si el tipo de bloque es ? es sorpresa y contiene un potenciador (P) o moneda (C). 
// Si el tipo de bloque es B es ladrillo y no contiene nada.
// Si el tipo de bloque es 0 es vacío y no contiene nada. 
// Si el tipo de bloque es H es oculto y contiene un potenciador o moneda.
bloque::bloque(Game* g, std::istream& is) :SceneObject(g, is), anim(0)

{
	game = g;
	// >> position.x >> position.y;
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
	colision.x = position.x;
	position.y = position.y * 32;
	colision.y = position.y;
	colision.w = colision.h = game->TILE_SIDE;
	texture = game->getTexture(Game::BLOQUE);
	anim = 0;

	/*
	position.x = pos.x*32;
	position.y = pos.y * 32;
	colision = { position.x , position.y, w, h };
	
	if (tipoAcc[0] == '?') {
		tipoBloque = sorpresa;

		if (tipoAcc[1] == 'P') {
			accionBloque = potenciador;
		}
		else if (tipoAcc[1] == 'C') {
			accionBloque = moneda;
		}
	}
	else if (tipoAcc[0] == 'B') {
		tipoBloque = ladrillo;
		accionBloque = nada;
	}
	else if (tipoAcc[0] == '0') {
		tipoBloque = vacio;
		accionBloque = nada;
	}
	else if (tipoAcc[0] == 'H') {
		tipoBloque = oculto;

		if (tipoAcc[1] == 'P') {
			accionBloque = potenciador;
		}
		else if (tipoAcc[1] == 'C') {
			accionBloque = moneda;
		}
	}

	texture = game->getTexture(Game::BLOQUE);
	anim = 0;
	*/
}
 bloque::~bloque()
{

}

// render del bloque en la pantalla
 void bloque::render() const
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
			texture->renderFrame(destRect, 0, anim);
		}
		else if (tipoBloque == vacio) {
			texture->renderFrame(destRect, 0, 4);
		}

		//texture->renderFrame(destRect, 0, 0);
	}
}

 // update del bloque
 void bloque::update()
 {
	 // se actualiza la animación del bloque
	 updateAnim();
 }

 void bloque::updateAnim()
 {
	 if (anim < 3) { anim++; }
	 else if (anim == 3) { anim = 0; }
 }

 // hit del bloque, si el jugador colisiona con el bloque se activa la acción del bloque
 void bloque::hit(SDL_Rect ataque, bool jugador)
 {
	 if (jugador) {
		 if (tipoBloque == sorpresa) {
			 if (accionBloque == moneda) {
				 game->grantPoints(100);
			 }
			 else if (accionBloque == potenciador) {
				 game->grantPoints(1000);
			 }
			 tipoBloque = vacio;
		 }
	 }
 }
