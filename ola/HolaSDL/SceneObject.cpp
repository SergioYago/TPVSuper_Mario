#include "SceneObject.h"
#include "gameList.h"
#include "Game.h"

SceneObject::SceneObject(Game* g, std::istream& is)
	:GameObject(g)
{
	is >> position.x >> position.y;
	width = g->TILE_SIDE;
	height = g->TILE_SIDE;
	colision = { position.x*g->TILE_SIDE, position.y*g->TILE_SIDE, width, height };
	velocity = { 0, 0 };
	isPlayer = false;
}

