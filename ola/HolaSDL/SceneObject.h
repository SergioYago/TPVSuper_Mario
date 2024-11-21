#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "Texture.h"
// abstract class SceneObject hereda de GameObject y luego todas las clases que heredan de SceneObject

class SceneObject : public GameObject
{
protected:
	Point2D position;
	Texture* texture;
	SDL_Rect colision;
	Point2D velocity;

public:
	SceneObject(Game* g);
	virtual void render() override;
	virtual void update() override;
	virtual void hit(SDL_Rect ataque, bool jugador) = 0;
};

