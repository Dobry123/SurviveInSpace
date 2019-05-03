#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Shotable.h"
#include <cmath>

namespace sis
{
	class SpaceShip :public Shotable
	{
	public:
		SpaceShip(sf::RenderWindow *window, AssetManager *assets);
		void update(float dt);
		void draw();
	private:
		//void shot();
		void move(float dt);
	};
}

#endif // !SPACESHIP_H