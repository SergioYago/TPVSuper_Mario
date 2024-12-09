#pragma once
#include "gameList.h"
// abstract class GameObject

using namespace std;

class PlayState;
class GameObject

{
private:
	GameList<GameObject>::anchor listAnchor;
protected:
	PlayState* game;
public:
	GameObject(PlayState* g);
	// destructora virtual
	virtual ~GameObject() {};
	virtual void render() const = 0;
	virtual void update() = 0;
	void setListAnchor(GameList<GameObject>::anchor a) { listAnchor = move(a); }
};

