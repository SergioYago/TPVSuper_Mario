#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "Texture.h"
#include "gameList.h"
// abstract class SceneObject hereda de GameObject y luego todas las clases que heredan de SceneObject

class SceneObject : public GameObject
{
protected:
	Point2D position;
	int width, height;
	SDL_Rect colision;
	Point2D velocity;
	bool player;
	GameList<SceneObject>::anchor anchor;

public:
	SceneObject(Game* g, Point2D pos, int w, int h, bool p);
	virtual void hit(SDL_Rect ataque, bool jugador) = 0;
	virtual void render() const = 0;
	virtual void update() = 0;
	// Method to set the list anchor
	void setListAnchor(GameList<SceneObject>::anchor anchor) {
		this->anchor = std::move(anchor);
	}
	
	SDL_Rect getCollisionRect()
	{
		return colision;
	}
	//virtual SceneObject* clone() const = 0;
};

