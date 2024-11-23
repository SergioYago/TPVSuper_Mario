#include "SceneObject.h"
#include "gameList.h"

SceneObject::SceneObject(Game* g, Point2D pos, int w, int h, bool p)
	:GameObject(g)
{
	position = pos;
	width = w;
	height = h;
	colision = { pos.x, pos.y, w, h };
	velocity = { 0, 0 };
	player = p;
}