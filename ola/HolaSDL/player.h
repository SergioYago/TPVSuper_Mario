#pragma once
#include "vector2D.h"
#include "checkML.h"
#include "Texture.h"

class Game;
class player
{
	Point2D position;
	Texture* texture;
	Game* game;
	int vidas;
	
public:
	player(Texture* texture, Vector2D<int> position, Game* g);
	~player();
	void render();
	void update();
	void hit();

};

