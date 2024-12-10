#pragma once

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include <functional>
#include "collision.h"
#include "Texture.h"
#include "TileMap.h"
#include "player.h"
#include "goomba.h"
#include "koopa.h"
#include "bloque.h"
#include "GameObject.h"
#include "gameList.h"
#include "PauseState.h"
#include "GameState.h"

using uint = unsigned int;
using SDLEventCallback = std::function<void(const SDL_Event&)>;

//
// Clase que representa el juego y controla todos sus aspectos
//
class PlayState :public GameState
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
	std::vector<SDLEventCallback> callbacks;

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

	// Lista de objetos del juego
	GameList<SceneObject> entities;
	// lista de objetos activos que se van a renderizar
	GameList<SceneObject*> activeEntities;


public:
	static constexpr uint WIN_WIDTH = 576;
	static constexpr uint WIN_HEIGHT = 512;
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint TILE_SIDE = 32;
	PlayState();
	~PlayState();
	int getMapOffset();
	void run();
	void loose();
	void update();
	Point2D checkMapColision(SDL_Rect collider);
	Point2D checkEntitieColision(SDL_Rect collider);
	bool checkBlockColision(char name, SDL_Rect collider);
	Collision CheckColision(SDL_Rect rect, Collision::Target target);
	void render()const;
	void handleEvents();
	void addEntity(SceneObject* entity);
	void connect(SDLEventCallback cb);
	void grantPoints(int points) { score += points; };
	int getPoints() const { return score; };
	bool isSupermario() const;
	int getMapOffset() const { return mapOffset; };
	SDL_Renderer* getRenderer();
	Texture* getTexture(TextureName name) const;

	// Constante globales



};

inline Texture*
PlayState::getTexture(TextureName name) const
{
	return textures[name];
}
inline SDL_Renderer*
PlayState::getRenderer()
{
	return renderer;
}