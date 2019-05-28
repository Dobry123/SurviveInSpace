#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include "Object.h"

namespace sis
{
	class Asteroid :public Object
	{
	public:
		Asteroid(sf::RenderWindow *window, AssetManager *assets, int difficult = 1);
		~Asteroid() {}
		void update(float dt);
		void draw();

	private:
		float animation_counter_;
		float animation_speed_;
		void move(float dt);
		void animate();
	};
}

#endif // !ASTEROID_H