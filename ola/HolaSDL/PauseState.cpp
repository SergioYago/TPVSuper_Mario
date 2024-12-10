#include "PauseState.h"
#include "PlayState.h"
PauseState::PauseState(PlayState* g)
{
	game = g;
	Button first = Button(game);
	//this->addEventListener();
	std::cout << "hola";
}
void PauseState::update()
{
	//boton no se ve
	//porque? --- el render no se llama
	//necesito meter un eventhandler y un gameobject (no un boton).
}
