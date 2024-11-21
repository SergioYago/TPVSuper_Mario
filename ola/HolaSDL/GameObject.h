#pragma once

// abstract class GameObject

using namespace std;

class Game;
class GameObject

{
protected:
	Game* game;
public:
	GameObject(Game* g);
	// destructora virtual
	virtual ~GameObject() {};
	virtual void render() = 0;
	virtual void update() = 0;



};

