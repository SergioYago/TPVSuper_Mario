#pragma once
#include "vector2D.h"
#include "checkML.h"
#include "Texture.h"
#include "Game.h"

class player
{
	Point2D position;
	Texture* texture;
	Game* game;
	
public:
	player(Texture* texture, Vector2D<int> position);
	~player();
	void render();
	void update();

};

