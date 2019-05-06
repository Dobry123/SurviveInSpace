#pragma once
#ifndef SHOT_H
#define SHOT_H

#include "Object.h"

namespace sis
{
	struct ShotStats
	{
		float range;
		int power;
		float hz;
		float speed;
	};

	class Shot :public Object
	{
	public:
		Shot(sf::RenderWindow *window, AssetManager *assets, Pose pose, ShotStats stats, int type = 0);
		~Shot() { };
		void draw();
		void update(float dt);
		bool isDead();
		int getPower();
	private:
		ShotStats stats_;
		void move(float dt);
		float distance_;
		bool toDestroy_;
	};
}

#endif // !SHOT_H
