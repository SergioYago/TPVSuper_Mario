#pragma once
#include "vector2D.h"
#include "checkML.h"
#include "Texture.h"
#include <SDL.h>

/*class Game;
class player
{
	Point2D position;
	Texture* texture;
	Game* game;
	int vidas;
	
public:
	player(Texture* texture, Vector2D<int> position, Game* g);
	~player();
	void render();
	void update();
	void hit();

};
*/

// Clase que representa al jugador. Como atributos tiene su posición actual, un puntero a su textura y un puntero al juego. Además , tiene un atributo para las vidas del jugador y para su dirección actual y su aspecto (Mario o super Mario). Tiene un método para renderizarlo, uno para actualizarlo (update), otro para restarle una vida (hit) y uno para los eventos de teclado (handleEvents).

class Game;
class player
{
	Vector2D<float> mapPosition;
	// posición relativa del jugador respecto al inicio del mapa
	Vector2D<float> screenPosition;

	Texture* texture;
	Game* game;
	int vidas;
	int direccion;
	int aspecto;
	int grounded = 0;
	int jump = 0;

	
public:
	bool hitted = false;
	SDL_Rect nextposition;
	player(std::istream& is, Game* g);
	~player();
	void render();
	void update();
	void hit();
	void handleEvents(SDL_Event event);
	//getter position
	Vector2D<float> getMapPosition() { return mapPosition; }
	Vector2D<float> getScreenPosition() { return screenPosition; }
	int getVidas() { return vidas; }
	int getDireccion() { return direccion; }
	int getAspecto() { return aspecto; }
	
	
	void igualaMovimiento();
	void VueltaPosicion();
	// cuando el jugador llega a la mitad de la pantalla e intenta avanzar, se incrementa el mapOffset porque se incrementa la posición del jugador en el mapa
	// , pero la posición en pantalla no cambia

};


