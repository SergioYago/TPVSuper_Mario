#pragma once
#include "Vector2D.h"
#include "Texture.h"

// clase de enemigo goomba que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posici�n actual, su direcci�n de movimiento, un puntero a su textura y un puntero al juego
class Game;
class goomba
{
	Point2D position;
	int direccion;
	Texture* texture;
	Game* game;
	bool isactive;
	
public:
	SDL_Rect nextposition;
	goomba(std::istream& is, Game* g);
	~goomba();
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

	void SetisActive(bool b) { isactive = b; }
	bool GetisActive() { return isactive; }
	int getDireccion() { return direccion; }
	//void igualaMovimiento();
	//void VueltaPosicion();
};

