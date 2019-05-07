#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Object.h"

namespace sis
{
	class Explosion :public Object
	{
	public:
		Explosion(sf::RenderWindow *window, AssetManager *assets, Pose pose);
		~Explosion() {}
		void update(float dt);
		void draw();
		bool isEnd();
	private:
		float animation_counter_;
		float animation_speed_;
		bool end_;
		void animate();
		void move(float dt);
	};
}

#endif // !EXPLOSION_H