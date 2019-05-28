#pragma once
#ifndef SHOTABLE_H
#define SHOTABLE_H

#include "Object.h"
#include "Shot.h"

namespace sis
{
	class Shotable :public Object
	{
	public:
		Shotable(sf::RenderWindow *window, AssetManager *assets) : Object(window, assets) { }
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual int getType() = 0;
		std::vector<Shot *> getShots() { return createdShots_; }
		bool ifShot() { return did_shot_; }
	protected:
		virtual void shot() = 0;
		virtual void move(float dt) = 0;
		std::vector<Shot *> createdShots_;
		bool did_shot_;
		ShotStats shot_stats_;
		sf::Clock clock_;
		float last_shot_time_;
	};
}

#endif // !SHOTABLE_H