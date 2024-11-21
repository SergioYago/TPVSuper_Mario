#pragma once
#include "SceneObject.h"

// abstract class Enemy hereda de SceneObject y es la clase base para todos los enemigos
class Enemy : public SceneObject
{
protected:


public:
	Enemy(Game* g);
	virtual void render() override;
	virtual void update() override;
	virtual void hit(SDL_Rect ataque, bool jugador);

};

