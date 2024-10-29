#pragma once
#include <SDL.h>
#include "Texture.h"
#include <string>
#include <iostream>

using namespace std;
using  uint = unsigned int;
class Game {

public:
	static const int TILE_SIDE = 32;  // constantes est�ticas en Game
	static const int WINDOW_WIDTH = 18;
	static const int WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;
	static const string TEXTURES_PATH;
	
	int mapOffset;
	// atributo de Game
	Game();


	enum TextureName {
		BACKGROUND,
		TILEMAP,
		NUM_TEXTURES,  // Truco C++: n�mero de texturas definidas
	};
	static Texture* cosas[NUM_TEXTURES];

private:
	
	
	
	
	// Ventana de la SDL (se destruir� en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	 
	
	
	// Array con todas las texturas del juego
	//std::array<Texture*, NUM_TEXTURES> ;

	void A�adir()
	{
		//cosas[1]= Texture(renderer, "../assets/imgs/blocks.png", 1, 1);
	}
};
