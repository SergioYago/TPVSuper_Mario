#pragma once
// abstract class GameObject

class Game;
class GameObject

{
protected:
	Game* game;
public:
	GameObject(Game* g);
	virtual void render() = 0;
	virtual void update() = 0;


};

