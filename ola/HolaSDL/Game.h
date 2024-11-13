#pragma once

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"
#include "TileMap.h"
#include "player.h"
#include "goomba.h"

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		PLAYER,
		GRANDE,
		GOOMBA,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool seguir;
	int mapOffset;


	// Objetos del juego
	TileMap* tilemap;
	player* mario;
	goomba* goombaa[15];

public:
	static constexpr uint WIN_WIDTH = 576;
	static constexpr uint WIN_HEIGHT = 512;
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint TILE_SIDE = 32;
	Game();
	~Game();
	int getMapOffset();
	void run();
	void loose();
	void update();
	void checkColision();
	void render() const;
	void handleEvents();
	
	Texture* getTexture(TextureName name) const;

	// Constante globales
	
	
	
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}