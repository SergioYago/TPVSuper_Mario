#pragma once
#include "vector2D.h"
#include "Texture.h"

//Clase del bloque, tiene como atributos la posición del bloque, el tipo de bloque como enumerado (ladrillo, sorpresa, vacío u oculto), 
// una acción (potenciador o moneda) tambien como enumerado, un puntero al juego y un puntero a la textura del bloque.
// Constructor, render, update y hit.
class Game;

class bloque
{
	Point2D position;
	Game* game;
	Texture* texture;
	enum tipo { ladrillo, sorpresa, vacio, oculto };
	enum accion { potenciador, moneda, nada };
	int anim;
	SDL_Rect colision;
	tipo tipoBloque;
	accion accionBloque;
public:
	bloque(std::istream& is, Game* g);
	~bloque();
	void render();
	void update();
	void hit();
	//getters
	Point2D getPosition() { return position; }
	tipo getTipo() { return tipoBloque; }
	accion getAccion() { return accionBloque; }
	SDL_Rect* getColision() { return &colision; }
};

