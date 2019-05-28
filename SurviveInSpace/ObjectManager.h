#pragma once
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "AssetManager.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "Shot.h"
#include "Player.h"
#include "Explosion.h"
#include "Level.h"
#include "CruiserEnemy.h"
#include "BoarderEnemy.h"
#include "Boss1.h"

namespace sis
{
	class ObjectManager
	{
	public:
		ObjectManager(sf::RenderWindow *window, AssetManager *assets, Player *player);
		~ObjectManager();
		void draw();
		int process(float dt, LevelData lvl_data);
		SpaceShip *getSpaceShip() { return spaceship_; }
		void clearEnemyObjects();
		void restartSpaceShipPosition();
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
		int cruisers_amount_;
		int boarders_amount_;
		bool boss_spawned_;
		bool boss_killed_;
		
		void checkCollisions();
		void processShots(float dt);
	};
}

#endif // !OBJECT_MANAGER_H