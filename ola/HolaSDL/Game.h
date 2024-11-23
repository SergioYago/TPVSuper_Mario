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
#include "koopa.h"
#include "bloque.h"
#include "GameObject.h"
#include "gameList.h"

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
		KOOPA,
		BLOQUE,
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
	string mapa1;
	string mapa2;
	int mapaActual;

	// Puntuación del jugador
	int score;


	// Vidas del jugador
	int lives;



	// Objetos del juego
	TileMap* tilemap;
	player* mario;
	goomba* goombaa[15];
	bloque* bloques[44];

	// Lista de objetos del juego
	GameList<SceneObject> entities;
	// lista de objetos activos que se van a renderizar
	GameList<SceneObject> activeEntities;

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
	bool checkMapColision( SDL_Rect collider);
	bool checkGoombaCollision(SDL_Rect collider);
	bool checkBlockColision(char name, SDL_Rect collider);
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