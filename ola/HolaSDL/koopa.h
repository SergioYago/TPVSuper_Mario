#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"

// clase de enemigo koopa que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posición actual, su dirección de movimiento, un puntero a su textura y un puntero al juego
class PlayState;
class koopa : public Enemy
{
	Texture* texture;

public:
	SDL_Rect nextposition;
	koopa(PlayState* g, Point2D pos, int w, int h, bool p, int points);
	//~koopa();
	void render() const override;
	void update() override;
	void mueveX();
	void mueveY();
	void igualaX(int i);
	void igualaY(int i);
	void VueltaX();
	void VueltaY();
	void ChangeDirection();
	//void igualaMovimiento();
	//void VueltaPosicion();

	//void hit() override;
};


