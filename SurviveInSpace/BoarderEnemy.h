#pragma once
#ifndef BOARDER_ENEMY_H
#define BOARDER_ENEMY_H

#include "Shotable.h"
#include <cmath>

namespace sis
{
	class BoarderEnemy :public Shotable
	{
	public:
		BoarderEnemy(sf::RenderWindow *window, AssetManager *assets, int difficult = 1);
		void update(float dt);
		void draw();
		int getType() { return 2; }

	private:
		bool move_reversed_x_;
		bool move_reversed_y_;
		std::random_device dev_;

		void shot();
		void move(float dt);
	};
}

#endif // !BOARDER_ENEMY_H