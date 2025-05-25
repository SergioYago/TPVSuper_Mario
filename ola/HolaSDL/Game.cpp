#include <string>

#include "Game.h"
#include "Block.h"
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
	{"firemario.png", 21, 1},
	{"goomba.png", 3, 1},
	{"blocks.png",6,1},
	{"koopa.png",4,1},
	{"mushroom.png",1,1},
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

	int i = 0;
	int f = 0;
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
			blocks.push_back(new Block(this, is));
		}
		else if (line[0] == 'G') {
			goombas.push_back(new goomba(is, this));
			
		}
		else if (line[0] == 'K') {
			koopas.push_back(new Koopa(is, this));
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

bool Game::checkEnemiesColision()
{
	return false;
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
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->render();
	}
	for(int i = 0; i < blocks.size();i++)
	{
		blocks[i]->render();
	}
	for(int i=0;i<koopas.size();i++)
	{
		koopas[i]->render();
	}
	for(int i =0;i<mushrooms.size();i++)
	{
		mushrooms[i]->render();
	}
	SDL_RenderPresent(renderer);
}
void
Game::checkColision()
{
//<<<<<<< Updated upstream


	
	/*mapOffset = 0;
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN);
		^*/
//>>>>>>> Stashed changes
}

bool Game::checkBlockColision(SDL_Rect rect, bool fromPlayer)
{
	int i = 0;
	SDL_Rect rect2;
	rect2.w = rect2.h = TILE_SIDE;
	bool collided = false;
	
	while (i < blocks.size() && !collided)
	{
		rect2.x = blocks[i]->returnPos().x;
		rect2.y = blocks[i]->returnPos().y;
		collided = (rect.x < rect2.x + rect2.w &&rect.x + rect.w > rect2.x &&rect.y < rect2.y + rect2.h &&rect.y + rect.h > rect2.y);
		i++;
	}
	if (collided && fromPlayer) 
	{
		i--;
		if (rect.y>rect2.y+rect2.h/2&&rect.x+rect.w>rect2.x+rect2.w/2) 
		{
			blocks[i]->active();
		}
	}
	return collided;
}

void Game::checkMushColision()
{
	SDL_Rect rect = mario->nextposition;
	SDL_Rect rect2;
	rect2.w = rect2.h = 32;
	bool colision = false;
	int i = 0;
	while(i<mushrooms.size()&&!colision)
	{
		rect2.x = mushrooms[i]->nextposition.x;
		rect2.y = mushrooms[i]->nextposition.y;
		colision = (rect.x < rect2.x + rect2.w && rect.x + rect.w > rect2.x && rect.y < rect2.y + rect2.h && rect.y + rect.h > rect2.y);
		i++;
	}
	if(colision)
	{
		mario->lvlUp();
		i--;
		auto it = find(mushrooms.begin(), mushrooms.end(), mushrooms[i]);
		mushrooms.erase(it);
	}
}

void
Game::update()
{
	mario->update();
	mario->mueveY();
	if(mario->nextposition.y+mario->nextposition.h>WIN_HEIGHT-26)
	{
		mario->looseLive();
		
	}
	else if (!tilemap->checkMapColision(mario->nextposition,mario->hitted)&&!checkBlockColision(mario->nextposition,true))
		{ 
		mario->igualaMovimientoy();
		mario->setIsGrounded(false);
	}
	else
		{
		// subir la misma cantidad que baja
		// se calcula restando la diferencia de alturas a 32 (32-diferencia de alturas)
			mario->VueltaPosiciony(); 
			mario->setIsGrounded(true);
		}
	checkMushColision();
	mario->mueveX();
	if (!tilemap->checkMapColision(mario->nextposition,mario->hitted) && !checkBlockColision(mario->nextposition,true))
	{
		mario->igualaMovimiento();
	}
	else 
	{
		mario->VueltaPosicionx();
	}
	checkMushColision();
	// Actualiza los objetos del juego
	//perro->update();
	// si mario llega a la mitad de la pantalla, incrementa el mapOffset
 	if (mario->getScreenPosition().x >= WIN_WIDTH/2 )
	{
		mapOffset = (mario->getMapPosition().x - mario->getScreenPosition().x);
	}
	for(int i=0;i<goombas.size();i++)
	{
		if (goombas[i]->getMapPos().x - mapOffset < WIN_WIDTH&& goombas[i]->getMapPos().x - mapOffset >-40) {
			goombas[i]->mueveY();
			if (!tilemap->checkMapColision(goombas[i]->nextposition, false)&&!checkBlockColision(goombas[i]->nextposition,false))
			{
				goombas[i]->igualaY(); 
			}
			else { goombas[i]->VueltaY(); }
			goombas[i]->mueveX();
			if (!tilemap->checkMapColision(goombas[i]->nextposition, false) && !checkBlockColision(goombas[i]->nextposition,false))
			{
				goombas[i]->igualaX();
			}
			else
			{
				goombas[i]->VueltaX();
			}
		}
		
	}
	for (int i = 0; i < koopas.size(); i++)
	{
		if (koopas[i]->getMapPos().x - mapOffset < WIN_WIDTH && koopas[i]->getMapPos().x - mapOffset >-40) {
			koopas[i]->mueveY();
			if (!tilemap->checkMapColision(koopas[i]->nextposition, false) && !checkBlockColision(koopas[i]->nextposition,false))
			{
				koopas[i]->igualaY();
			}
			else { koopas[i]->VueltaY(); }
			koopas[i]->mueveX();
			if (!tilemap->checkMapColision(koopas[i]->nextposition, false) && !checkBlockColision(koopas[i]->nextposition,false))
			{
				koopas[i]->igualaX();
			}
			else
			{
				koopas[i]->VueltaX();
			}
		}

	}
	for (int i = 0; i < mushrooms.size(); i++)
	{
		if (mushrooms[i]->getMapPos().x - mapOffset < WIN_WIDTH && mushrooms[i]->getMapPos().x - mapOffset >-40) {
			mushrooms[i]->mueveY();
			if (!tilemap->checkMapColision(mushrooms[i]->nextposition, false) && !checkBlockColision(mushrooms[i]->nextposition, false))
			{
				mushrooms[i]->igualaY();
			}
			else { mushrooms[i]->VueltaY(); }
			mushrooms[i]->mueveX();
			if (!tilemap->checkMapColision(mushrooms[i]->nextposition, false) && !checkBlockColision(mushrooms[i]->nextposition, false))
			{
				mushrooms[i]->igualaX();
			}
			else
			{
				mushrooms[i]->VueltaX();
			}
		}

	}
	for(int i=0;i<44;i++)
	{
		blocks[i]->update();
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
			mario->handleEvents(evento);
		}
		else if (evento.type == SDL_KEYUP) {
			//perro->handleEvent(evento);
			mario->handleEvents(evento);
		}
	}
}
void Game::loose()
{
	seguir = false;
}
void Game::generateMushroom(Point2D pos)
{
	pos.y = pos.y - 32;
	mushrooms.push_back(new Mushroom(pos, this));
}