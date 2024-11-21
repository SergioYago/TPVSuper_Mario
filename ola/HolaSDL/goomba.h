#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"

// clase de enemigo goomba que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posici�n actual, su direcci�n de movimiento, un puntero a su textura y un puntero al juego
class Game;
class goomba : public Enemy
{
	Texture* texture;
	
public:
	SDL_Rect nextposition;
	goomba(std::istream& is, Game* g);
	~goomba();
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

