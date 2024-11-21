#include "Enemy.h"

// Constructor de la clase Enemy

Enemy::Enemy(Game* g)
	:SceneObject(g)
{
	player = false;
}

// Método hit de los enemigos, se encarga de recibir el ataque del jugador y restarle vida al enemigo o hacerle daño

void Enemy::hit(SDL_Rect ataque, bool jugador)
{
	if (jugador)
	{
		if (SDL_HasIntersection(&ataque, &colision) && ataque.y >= colision.y) //&& el mario no esta encima)
		{
			//mario pierde vida
			cout << "Mario pierde vida" << endl;
		}
		else if (SDL_HasIntersection(&ataque, &colision) && ataque.y < colision.y) //&& el mario esta encima)
		{
			// se muere el enemigo
			cout << "Enemigo muere" << endl;
		}
	}
}
