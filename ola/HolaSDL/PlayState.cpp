#include "PlayState.h"
#include <string>
#include <SDL.h>
#include <SDL_rect.h>

using namespace std;

// Formato de la especificaci?n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// N?mero de frames por fila
	uint numRows;		// N?mero de frames por columna
};

// Directorio ra?z de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificaci?n de las texturas del juego
const array<TextureSpec, PlayState::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 12, 1},
	{"supermario.png",22,1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"blocks.png", 6, 1},
};

PlayState::PlayState()
	: seguir(true)
{
	// Inicializa la SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "Error initializing SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	window = SDL_CreateWindow("First test with SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		cerr << "Error creating window: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		cerr << "Error creating renderer: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);
	}

	cout << "Loading entities..." << endl;
	// Lee el archivo de entidades de juego y crea las entidades, llamando a sus constructores con los datos leidos
	ifstream file("../assets/maps/world1.txt");
	if (!file.is_open()) {
		cerr << "Error opening file: ../assets/maps/world1.txt" << endl;
		exit(1);
	}

	string line;
	int i = 0;
	int j = 0;
	while (getline(file, line))
	{
		istringstream is(line.substr(1));
		if (line[0] == 'M') {
			Point2D pos;
			is >> pos.x >> pos.y;
			mario = new player(this, pos, TILE_SIDE, TILE_SIDE, true);
			entities.push_back(mario);
		}
		else if (line[0] == 'B') {
			Point2D pos;
			is >> pos.x >> pos.y;
			string tipo;
			is >> tipo;
			entities.push_back(new bloque(this, pos, TILE_SIDE, TILE_SIDE, false, tipo));
		}
		else if (line[0] == 'G') {
			Point2D pos;
			is >> pos.x >> pos.y;
			entities.push_back(new goomba(this, pos, TILE_SIDE, TILE_SIDE, false, 50));
		}
		else if (line[0] == 'K') {
			Point2D pos;
			is >> pos.x >> pos.y;
			entities.push_back(new koopa(this, pos, TILE_SIDE, TILE_SIDE, false, 50));
		}
	}

	mapaActual = 1;
	mapa1 = "../assets/maps/world1.csv";
	mapa2 = "../assets/maps/world2.csv";
	if (mapaActual == 1)
	{
		tilemap = new TileMap(mapa1, this);
	}
	else
	{
		tilemap = new TileMap(mapa2, this);
	}


	cout << "Initialization complete." << endl;
}

PlayState::~PlayState()
{
	cout << "Cleaning up resources..." << endl;
	// Elimina los objetos del juego
	delete tilemap;

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	cout << "Cleanup complete." << endl;
}

int PlayState::getMapOffset() {
	return mapOffset;
}

void PlayState::run()
{
	cout << "Starting main PlayState loop..." << endl;
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteraci�n
		uint32_t inicio = SDL_GetTicks();
		render();
		update();       // Actualiza el estado de los objetos del juego
		// Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
	cout << "Exiting main PlayState loop..." << endl;
}

void
PlayState::render() const
{
	SDL_RenderClear(renderer);
	if (mapaActual == 1) {
		SDL_SetRenderDrawColor(renderer, 100, 100, 500, 100);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	}

	// Pinta los objetos del juego

	tilemap->renderTileMap();
	//mario->render();


	// renderiza las entidades de la lista de entidades

	for (const SceneObject* entitie : entities)
	{
		entitie->render();
	}


	SDL_RenderPresent(renderer);
}


Point2D
PlayState::checkEntitieColision(SDL_Rect collider)
{
	Point2D aux;
	bool colision = false;
	SDL_Rect aux2;
	for (auto entitie : entities)
	{
		aux2 = entitie->getCollisionRect();
		colision = SDL_HasIntersection(&aux2, &collider);
		//se hace esto para que no compruebe consigo mismo
		if (colision && &collider == &aux2)
		{
			colision = false;
		}
		if (colision)
		{
			aux.x = entitie->getCollisionRect().x - collider.x;
			aux.y = entitie->getCollisionRect().y - collider.y;
			break;
		}
	}
	return aux;
}

Collision
PlayState::CheckColision(SDL_Rect rect, Collision::Target target)
{
	Collision aux;
	if (target == 0)
	{
		if (tilemap->checkMapColision(rect, true))
		{
			aux.horizontal = aux.vertical = -100;
		}
		else
		{
			Point2D direction;
			direction = checkEntitieColision(rect);
			if (direction.x != 0 || direction.y != 0)
			{

				aux.horizontal = direction.x;
				aux.vertical = direction.y;
			}
		}

	}
	else if (target == 1)
	{
		if (tilemap->checkMapColision(rect, true))
		{
			aux.horizontal = aux.vertical = -100;
			//ns c�mo ponerlos
		}
		else
		{
			Point2D direction;
			direction = checkEntitieColision(rect);
			if (direction.x != 0 || direction.y != 0)
			{
				aux.horizontal = direction.x - 32;
				aux.vertical = direction.y;

			}
		}

	}
	else if (target == 2)
	{
		if (tilemap->checkMapColision(rect, true))
		{
			aux.horizontal = aux.vertical = -100;
			//ns c�mo ponerlos
		}
		else
		{
			Point2D direction;
			direction = checkEntitieColision(rect);
			if (direction.x != 0 || direction.y != 0)
			{
				aux.horizontal = -30;
				aux.vertical = direction.y;

			}
		}
	}
	//mira el mapa y las entidades, pero entonces 
	// tenemos que hacer que el struct de target apunte a bot
	//chequea enemigos, solo para player
	//chequea bloques, para ambos de nuevo
	return aux;
}

void
PlayState::update()
{
	//mario->update();
	for (auto entitie : entities)
	{
		entitie->update();

	}
	if (mario->getScreenPosition().x == WIN_WIDTH / 64)
	{
		mapOffset = (mario->getMapPosition().x - mario->getScreenPosition().x) * 32;

	}

}

void
PlayState::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {
			//perro->handleEvent(evento);
			if (evento.key.keysym.sym == SDLK_ESCAPE)
			{
				
				PauseState pause=PauseState(this);
			}
			else { mario->handleEvents(evento); }
		}
		else if (evento.type == SDL_KEYUP) {
			//perro->handleEvent(evento);
			mario->handleEvents(evento);
		}
	}
}
void PlayState::loose()
{
	seguir = false;
}
void PlayState::addEntity(SceneObject* entity)
{
	entities.push_back(entity);
}
bool PlayState::isSupermario() const
{
	if (mario->getAspecto() >= 1) { return true; }
	else { return false; }
}
void
PlayState::connect(SDLEventCallback cb)
{
	callbacks.push_back(cb);
}