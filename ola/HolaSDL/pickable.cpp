#include "pickable.h"

pickable::pickable(Game* g, Point2D pos, int w, int h, bool p, int action)
	:SceneObject(g, pos, w, h, p)
{
	this->action = action;
}