#include "coin.h"

coin::coin(Game* g, Point2D pos, int w, int h, bool p)
	:pickable(g, pos, w, h, p, 1)
{
}


