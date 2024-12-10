#pragma once
#include <fstream>
#include <string>
#include "GameState.h"
#include"button.h"
class PlayState;
class PauseState : public GameState
{
private:
	PlayState* game;
	
public:
	PauseState(PlayState* g);
	void update() override;
};

