#pragma once
#include "Vector2D.h"
#include "Texture.h"

// clase de enemigo koopa que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posición actual, su dirección de movimiento, un puntero a su textura y un puntero al juego
class Game;
class koopa
{
	Point2D position;
	int direccion;
	Texture* texture;
	Game* game;
	Point2D velocity;

public:
	SDL_Rect nextposition;
	koopa(std::istream& is, Game* g);
	~koopa();
	void render();
	void update();
	void hit();
	void mueveX();
	void mueveY();
	void igualaX();
	void igualaY();
	void VueltaX();
	void VueltaY();
	void ChangeDirection();
	void SetisActive(bool b) {  }
	bool GetisActive() {  }
	int getDireccion() {  }
	//void igualaMovimiento();
	//void VueltaPosicion();
};


