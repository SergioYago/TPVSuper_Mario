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
	SDL_Rect nextposition;
public:
	
	goomba(Game* g, Point2D pos, int w, int h, bool p, int points);
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
	SDL_Rect* GetNextPosition() { return &nextposition; }
	//void igualaMovimiento();
	//void VueltaPosicion();
};

