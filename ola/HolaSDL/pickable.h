#pragma once
#include "SceneObject.h"
class pickable : public SceneObject
{
protected:
	// 0 = seta, 1 = coin
	int action;
public:
	pickable(PlayState* g, Point2D pos, int w, int h, bool p, int action);
	// metodo virtual puro triggerAction que se implementa en las clases hijas
	virtual void triggerAction() = 0;


};