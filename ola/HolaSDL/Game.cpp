#include <string>

#include "Game.h"

using namespace std;

// Formato de la especificaci�n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// N�mero de frames por fila
	uint numRows;		// N�mero de frames por columna
};

// Directorio ra�z de los archivos de textura
const string textureRoot = "../assets/imgs/";

// Especificaci�n de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 12, 1},
	//{"helicopter.png", 5, 1},
};

Game::Game()
	: seguir(true)
{
	
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	// Lee el archivo de entidades de juego y crea las entidades, llamando a sus constructores con los datos leidos
	ifstream file("../assets/maps/world1.txt");
	string line;

	while (getline(file, line))
	{
		// Crea una entidad de juego
		// si la primera letra de la linea es 'M', crea al player
		// si la primera letra de la linea es 'B', crea un bloque
		// si la primera letra de la linea es 'G', crea un goomba
		// si la primera letra de la linea es 'K', crea un koopa

		// crear un istream a partir de la linea, incluyendo todo el contenido de la linea menos el primer caracter
		istringstream is(line.substr(1));
		
		if (line[0] == 'M') {
			mario = new player(is, this);
		}
		else if (line[0] == 'B') {

		}
		else if (line[0] == 'G') {

		}
		else if (line[0] == 'K') {

		}
		
		//entities.push_back(new Entity(this, line));
	}

	// Crea los objetos del juego
	//perro = new Dog(this, -textures[DOG]->getFrameWidth(), 390);
	tilemap = new TileMap("../assets/maps/world1.csv", this);
}

Game::~Game()
{
	// Elimina los objetos del juego
	delete tilemap;

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int
Game::getMapOffset() {
	return mapOffset;
}

void
Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteraci�n
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		checkColision();
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,100,100,500,100);

	// Pinta los objetos del juego
	//textures[BACKGROUND]->render();
	//perro->render();
	tilemap->renderTileMap();
	mario->render();

	SDL_RenderPresent(renderer);
}
void
Game::checkColision()
{

}

void
Game::update()
{
	mario->update();
	// Actualiza los objetos del juego
	//perro->update();
	// si mario llega a la mitad de la pantalla, incrementa el mapOffset
 	if (mario->getScreenPosition().x == WIN_WIDTH / 64)
	{
		mapOffset = (mario->getMapPosition().x - mario->getScreenPosition().x)*50;
	}
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {
			//perro->handleEvent(evento);
		}
	}
}
void Game::loose()
{
	seguir = false;
}