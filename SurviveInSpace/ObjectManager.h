#pragma once
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "AssetManager.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "Shot.h"
#include "Player.h"
#include "Explosion.h"

namespace sis
{
	class ObjectManager
	{
	public:
		ObjectManager(sf::RenderWindow *window, AssetManager *assets, Player *player);
		~ObjectManager();
		void draw();
		void process(float dt);
	private:
		sf::RenderWindow *window_;
		AssetManager *assets_;
		Player *player_;
		std::vector<Shot *> spaceship_shots_;
		std::vector<Shot *> enemy_shots_;
		std::vector<Asteroid *> asteroids_;
		std::vector<Shotable *> enemies_;
		std::vector<Explosion *> explosions_;
		SpaceShip *spaceship_;
		void checkCollisions();
		void processShots(float dt);
	};
}

#endif // !OBJECT_MANAGER_H