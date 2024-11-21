#include "SceneObject.h"

SceneObject::SceneObject(Game* g)
	:GameObject(g)
{
	position = Point2D(0, 0);
	colision = { 0,0,0,0 };
	velocity = Point2D(0, 0);

}

void SceneObject::render()
{
}