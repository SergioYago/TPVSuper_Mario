#pragma once
#include "Vector2D.h"
#include "checkML.h"
#include "Texture.h"
#include <SDL.h>
#include "SceneObject.h"

// Clase que representa al jugador. Como atributos tiene su posici�n actual, un puntero a su textura y un puntero al juego. Adem�s , tiene un atributo para las vidas del jugador y para su direcci�n actual y su aspecto (Mario o super Mario). Tiene un m�todo para renderizarlo, uno para actualizarlo (update), otro para restarle una vida (hit) y uno para los eventos de teclado (handleEvents).

class Game;
class player:public SceneObject
{
	Vector2D<float> mapPosition;
	// posici�n relativa del jugador respecto al inicio del mapa
	Vector2D<float> screenPosition;

	Texture* peque;
	Texture* grandote;
	Game* game;
	int vidas;
	int direccion;
	int aspecto;
	bool isGrounded;
	int jump;
	int anim;

	
public:
	bool hitted = false;
	SDL_Rect colision;
	player(Game* g,Point2D pos, int w, int h, bool p);
	//~player();
	void render() const override;
	void update()override;
	void hit(SDL_Rect ataque, bool jugador) override ;
	void handleEvents(const SDL_Event event);
	void updateAnim();
	//getter position
	Vector2D<float> getMapPosition() { return mapPosition; }
	Vector2D<float> getScreenPosition() { return screenPosition; }
	int getVidas() { return vidas; }
	int getDireccion() { return direccion; }
	int getAspecto() { return aspecto; }

	// setter isGrounded
	void setIsGrounded(bool b) { isGrounded = b; }
	
	void mueveX();
	void mueveY();
	void igualaMovimiento(int i);
	void igualaMovimientoy(int i);
	void VueltaPosicionx();
	void VueltaPosiciony();
	int GetJump() { return jump; }
	void SetJump(int i) {
		jump = i;
		std::cout <<"";
	}
	void SetAspecto(int i) { aspecto = i; }
	// cuando el jugador llega a la mitad de la pantalla e intenta avanzar, se incrementa el mapOffset porque se incrementa la posici�n del jugador en el mapa
	// , pero la posici�n en pantalla no cambia

};


