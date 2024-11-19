#pragma once
#include "Vector2D.h"
#include "Texture.h"

class Game;
class champi
{
	Point2D position;
	int direccion;
	Texture* texture;
	Game* game;
	bool isactive;

public:
	SDL_Rect nextposition;
	champi(std::istream& is, Game* g);
	~champi();
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

