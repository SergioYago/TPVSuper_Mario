#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "SceneObject.h"

//Clase del bloque, tiene como atributos la posición del bloque, el tipo de bloque como enumerado (ladrillo, sorpresa, vacío u oculto), 
// una acción (potenciador o moneda) tambien como enumerado, un puntero al juego y un puntero a la textura del bloque.
// Constructor, render, update y hit.
class PlayState;

class bloque : public SceneObject
{
	Texture* texture;
	enum tipo { ladrillo, sorpresa, vacio, oculto };
	enum accion { potenciador, moneda, nada };
	int anim;
	tipo tipoBloque;
	accion accionBloque;
public:
	bloque(PlayState* g, Point2D pos, int w, int h, bool p, string tipoAcc);
	~bloque();
	void render() const override;
	void update() override;
	void hit(SDL_Rect ataque, bool jugador) override;
	void setTipo(){tipoBloque = vacio;}
	void updateAnim();
	//getters
	Point2D getPosition() { return position; }
	tipo getTipo() { return tipoBloque; }
	accion getAccion() { return accionBloque; }
	

};

