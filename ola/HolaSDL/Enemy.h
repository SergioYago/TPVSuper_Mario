#pragma once
#include "SceneObject.h"

// abstract class Enemy hereda de SceneObject y es la clase base para todos los enemigos
class Enemy : public SceneObject
{
protected:
	int puntos;

public:
	Enemy(Game* g, Point2D pos, int w, int h, bool p, int points);

	void hit(SDL_Rect ataque, bool jugador) override;

};

