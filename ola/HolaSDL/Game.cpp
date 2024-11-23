#include <string>
#include <SDL.h>
#include <SDL_rect.h>
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
const string textureRoot = "../assets/images/";

// Especificaci�n de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 12, 1},
	{"supermario.png",22,1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"blocks.png", 6, 1},
	//{"helicopter.png", 5, 1},
};

Game::Game()
	: seguir(true)
{
	cout << "Initializing SDL..." << endl;
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

	cout << "Loading textures..." << endl;
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
			mario = new player(is, this);
		}
		else if (line[0] == 'B') {
			bloques[j] = new bloque(is, this);
			j++;
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

	mapa1 = "../assets/maps/world1.csv";
	mapa2 = "../assets/maps/world2.csv";
	tilemap = new TileMap(mapa1, this);

	cout << "Initialization complete." << endl;
}

Game::~Game()
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

int Game::getMapOffset() {
	return mapOffset;
}

void Game::run()
{
	cout << "Starting main game loop..." << endl;
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
	cout << "Exiting main game loop..." << endl;
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

	for (int i = 0; i < 44; i++)
	{
			bloques[i]->render();
		
	}
	/*
	for (int i = 0; i < 14; i++)
	{
		//if (goombaa[i]->GetisActive())
		//{
			goombaa[i]->render();
		//}
	}
	*/

	// renderiza las entidades de la lista de entidades
	for (SceneObject* entity : entities) {
		if (entity != nullptr) {
			entity->render();
		}
		else {
			cerr << "Warning: Null entity found in entities list." << endl;
		}
	}



	SDL_RenderPresent(renderer);
}
bool
Game::checkMapColision( SDL_Rect collider)
{
	
	bool colision =tilemap->checkMapColision(collider,true);
	return colision;
}
bool
Game::checkGoombaCollision(SDL_Rect collider)
{	
	SDL_Rect aux;
	aux.x = 0; aux.y = 0;
	aux.h = 0; aux.w = 0;
	int j = 0;
	int colision = 0;
	while(j<14&&!colision)
	{
		colision =SDL_IntersectRect(&collider, &goombaa[j]->nextposition,&aux);
		if (colision==1)
		{
			colision == (aux.h<=aux.w && mario->getDireccion() == 0) + 1;
			//goombaa[j]->hit();
		}
	}
	return colision;
}
bool Game::checkBlockColision(char name, SDL_Rect collider)
{
	SDL_Rect aux;
	aux.x = aux.y = 0;
	aux.w = aux.h = 0;
	bool colision = false;
	int j = 0;
	while(!colision&&j<44)
	{
		colision = SDL_IntersectRect(&collider, bloques[j]->getColision(),&aux);
		j++;
	}
	if (colision&&name=='p')
	{
		if (aux.h<aux.w&&mario->GetJump()>0)
		{
			//si es ladrillo
		if (bloques[j]->getTipo()==0&&mario->getAspecto()==1)
		{
			bloques[j]->~bloque();
		}
		//si es sorpresa
		else if (bloques[j]->getTipo()==1)
		{
		//spawn cosas
			bloques[j]->setTipo();
		}
		//si es oculto
		else if (bloques[j]->getTipo()==3)
		{
			bloques[j]->setTipo();
		}
		}
		else if (bloques[j]->getTipo() == 3) { colision = false; }
	}
	
	
	return colision;
}

void
Game::update()
{
	mario->update();
	for (int i =0;i<14;i++)
	{
		goombaa[i]->update();
	}
	
	/*SDL_Rect aux;
	aux.x = aux.y = 0;
	aux.w = aux.h = 0;
	mario->update();
	mario->mueveY();
	int colision = false;
	int j = 0;
	while(!colision&&j<44)
	{
		colision = SDL_HasIntersection(&mario->nextposition, bloques[j]->getColision());
		j++;
	}
	
	if (!tilemap->checkMapColision(mario->nextposition,mario->hitted)&&!colision)
		{ 
		
		mario->igualaMovimientoy();
		mario->setIsGrounded(false);
			
	}
	else
	{
		if (colision == true&&mario->GetJump() >= 1)
		{
			mario->SetJump(0);
			mario->setIsGrounded(false);
		}
		else {
			// subir la misma cantidad que baja
			// se calcula restando la diferencia de alturas a 32 (32-diferencia de alturas)
			mario->VueltaPosiciony();
			mario->setIsGrounded(true);
		}
	}
	mario->mueveX();
	 j = 0;
	 colision = false;
	while (!colision && j < 44) 
	{
		colision = SDL_HasIntersection(&mario->nextposition, bloques[j]->getColision());
			j++;
	}
	if (!tilemap->checkMapColision(mario->nextposition,mario->hitted)&&!colision)
	{mario->igualaMovimiento();}
	else 
	{
		mario->VueltaPosicionx();
	}
	for (int i = 0; i < 14; i++)
	{
		
		if (goombaa[i]->GetisActive()&& SDL_IntersectRect(&goombaa[i]->nextposition, &mario->nextposition, &aux))
		{
			if (aux.w > aux.h && mario->GetJump() == 0)
			{
				goombaa[i]->SetisActive(false);
			}
			else
			{
				//jugador muere
			}
		}
	}
	// Actualiza los objetos del juego
	//perro->update();
	// si mario llega a la mitad de la pantalla, incrementa el mapOffset*/
 	if (mario->getScreenPosition().x == WIN_WIDTH / 64)
	{
		mapOffset = (mario->getMapPosition().x - mario->getScreenPosition().x)*32;
		
	}
	/*
	
	for(int i=0;i<14;i++)
	{
		if (goombaa[i]->GetisActive()) 
		{
			goombaa[i]->mueveY();
			if (!tilemap->checkMapColision(goombaa[i]->nextposition, true))
			{
				goombaa[i]->VueltaY();
			}
			else { goombaa[i]->igualaY(); }
			
			goombaa[i]->mueveX();
			if (!tilemap->checkMapColision(goombaa[i]->nextposition, true))
			{
				goombaa[i]->igualaX();
			}
			else { goombaa[i]->ChangeDirection(); }
		}
		if (SDL_IntersectRect(&goombaa[i]->nextposition, &mario->nextposition, &aux))
		{
			if (aux.w > aux.h && mario->GetJump() == 0)
			{
				goombaa[i]->SetisActive(false);
			}
			else
			{
				//jugador muere
			}
		}
		
	}*/
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
void Game::addEntity(SceneObject* entity)
{
	entities.push_back(entity);
}
bool Game::isSupermario() const
{
	if (mario->getAspecto() >= 1) { return true; }
	else { return false; }
}