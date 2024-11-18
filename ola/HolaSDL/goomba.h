#pragma once
#include "Vector2D.h"
#include "Texture.h"

// clase de enemigo goomba que se mueve y detecta colisiones con el mapa y con el jugador
// contiene su posición actual, su dirección de movimiento, un puntero a su textura y un puntero al juego
class Game;
class goomba
{
	Vector2D<float> screenPos;
	Vector2D<float> mapPos;
	Point2D position;
	int direccion;
	Texture* texture;
	Game* game;
	
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
	Vector2D<float> getScreenPos() { return screenPos; }
	Vector2D<float> getMapPos() { return mapPos; }
	int getDireccion() { return direccion; }
	//void igualaMovimiento();
	//void VueltaPosicion();
};

