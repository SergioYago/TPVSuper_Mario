#pragma once
#include "Vector2D.h"
#include "Texture.h"

class Game;
class Mushroom
{
	Vector2D<float> screenPos;
	Vector2D<float> mapPos;
	int direccion;
	Texture* texture;
	Game* game;
	
public:
	SDL_Rect nextposition;
	Mushroom(Point2D pos, Game* g);
	~Mushroom();
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

