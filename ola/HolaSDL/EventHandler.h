#pragma once
#include <SDL.h>
#include "gameList.h"

class EventHandler
{
	public:
	void virtual handleEvent(const SDL_Event evento )=0;
};

