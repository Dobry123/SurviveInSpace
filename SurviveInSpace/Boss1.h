#pragma once
#ifndef BOSS1_ENEMY_H
#define BOSS1_ENEMY_H

#include "Shotable.h"
#include <cmath>

namespace sis
{
	class Boss1 :public Shotable
	{
	public:
		Boss1(sf::RenderWindow *window, AssetManager *assets, int difficult = 1);
		void update(float dt);
		void draw();
		int getType() { return 90; }

	private:
		bool move_reversed_x_;
		bool move_reversed_y_;
		std::random_device dev_;

		void shot();
		void move(float dt);
	};
}

#endif // !BOSS1_ENEMY_H