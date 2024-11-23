#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"

// clase de enemigo goomba que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posición actual, su dirección de movimiento, un puntero a su textura y un puntero al juego
class Game;
class goomba : public Enemy
{
	Texture* texture;
	
public:
	SDL_Rect nextposition;
	goomba(Game* g, Point2D pos, int w, int h, bool p, int points);
	//~goomba();
	void render() override;
	void update() override;
	void mueveX();
	void mueveY();
	void igualaX();
	void igualaY();
	void VueltaX();
	void VueltaY();
	void ChangeDirection();

	//void igualaMovimiento();
	//void VueltaPosicion();
};

