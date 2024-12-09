#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"

// clase de enemigo goomba que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posici�n actual, su direcci�n de movimiento, un puntero a su textura y un puntero al juego
class PlayState;
class goomba : public Enemy
{
	Texture* texture;
	SDL_Rect colision;
public:
	
	goomba(PlayState* g, Point2D pos, int w, int h, bool p, int points);
	//~goomba();
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
};

