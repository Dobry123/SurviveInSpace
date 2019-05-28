#pragma once
#ifndef CRUISER_ENEMY_H
#define CRUISER_ENEMY_H

#include "Shotable.h"
#include <cmath>

namespace sis
{
	class CruiserEnemy :public Shotable
	{
	public:
		CruiserEnemy(sf::RenderWindow *window, AssetManager *assets, int difficult = 1);
		void update(float dt);
		void draw();
		int getType() { return 1; }

	private:
		bool move_reversed_;
		std::random_device dev_;

		void shot();
		void move(float dt);
	};
}

#endif // !CRUISER_ENEMY_H