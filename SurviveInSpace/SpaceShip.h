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
		void setPosition(float x, float y);

		int getShotPower() { return shot_stats_.power; }
		float getShotHz() { return shot_stats_.hz; }
		float getShotRange() { return shot_stats_.range; }
		float getShotSpeed() { return shot_stats_.speed; }
		int getShotsNumber() { return shots_number_; }

		void upgradeShotPower() { shot_stats_.power += 25; }
		void upgradeShotHz() { shot_stats_.hz += 2; }
		void upgradeShotRange() { shot_stats_.range += 25; }
		void upgradeShotSpeed() { shot_stats_.speed += 25; }
		void addHp() { hp_ += 50; }
		void upgradeShotsNumber() { ++shots_number_; }

		int getType() { return 0; }
	private:
		int shots_number_;

		void shot();
		void move(float dt);
	};
}

#endif // !SPACESHIP_H