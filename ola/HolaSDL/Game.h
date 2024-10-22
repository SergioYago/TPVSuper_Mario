#pragma once
#include <SDL.h>
#include "Texture.h"
#include <string>
#include <iostream>

using namespace std;
using  uint = unsigned int;
class Game {

public:
	static const int TILE_SIDE = 32;  // constantes estáticas en Game
	static const int WINDOW_WIDTH = 18;
	static const int WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;

	enum TextureName {
		BACKGROUND,
		TILEMAP,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	//std::array<Texture*, NUM_TEXTURES> ;


};
