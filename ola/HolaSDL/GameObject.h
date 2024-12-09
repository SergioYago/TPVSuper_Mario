#pragma once
#include "gameList.h"
// abstract class GameObject

using namespace std;

class Game;
class GameObject

{
private:
	GameList<GameObject>::anchor listAnchor;
protected:
	Game* game;
public:
	GameObject(Game* g);
	// destructora virtual
	virtual ~GameObject() {};
	virtual void render() const = 0;
	virtual void update() = 0;
	void setListAnchor(GameList<GameObject>::anchor a) { listAnchor = move(a); }
};

