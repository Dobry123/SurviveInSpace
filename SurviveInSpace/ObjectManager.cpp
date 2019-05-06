#include "ObjectManager.h"
#include <iostream>

namespace sis
{
	ObjectManager::ObjectManager(sf::RenderWindow *window, AssetManager *assets, Player *player)
	{
		window_ = window;
		assets_ = assets;
		player_ = player;

		spaceship_ = new SpaceShip(window_, assets_);
	}

	ObjectManager::~ObjectManager()
	{
		delete spaceship_;
	}

	void ObjectManager::process(float dt)
	{
		checkCollisions();

		// update spaceship
		spaceship_->update(dt);

		processShots(dt);

		// spawn asteroids
		if (asteroids_.size() < 50)
		{
			int spawn = 50 - asteroids_.size();
			for (int i = 0; i < spawn; ++i)
				asteroids_.push_back(new Asteroid(window_, assets_));
		}

		// update asteroids
		for (int i = 0; i < asteroids_.size(); ++i)
		{
			asteroids_[i]->update(dt);
		}
	}

	void ObjectManager::draw()
	{
		spaceship_->draw();

		for (int i = 0; i < asteroids_.size(); ++i)
		{
			asteroids_[i]->draw();
		}

		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			spaceship_shots_[i]->draw();
		}
	}

	void ObjectManager::processShots(float dt)
	{
		// crate new spaceship shots
		if (spaceship_->ifShot())
		{
			spaceship_shots_.push_back(spaceship_->getShots()[0]);
		}

		// update spaceship shots
		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			if (spaceship_shots_[i]->isDead())
			{
				delete spaceship_shots_[i];
				spaceship_shots_.erase(spaceship_shots_.begin() + i);
				if (i > 0)
					--i;
			}
			else
				spaceship_shots_[i]->update(dt);
		}
	}

	void ObjectManager::checkCollisions()
	{
		// check shots and asteroids
		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			for (int j = 0; j < asteroids_.size(); ++j)
			{
				float d = std::sqrtf((spaceship_shots_[i]->getPose().x - asteroids_[j]->getPose().x)
					* (spaceship_shots_[i]->getPose().x - asteroids_[j]->getPose().x)
					+ (spaceship_shots_[i]->getPose().y - asteroids_[j]->getPose().y)
					* (spaceship_shots_[i]->getPose().y - asteroids_[j]->getPose().y));
				if (d < spaceship_shots_[i]->getR() + asteroids_[j]->getR())
				{
					asteroids_[j]->hit(spaceship_shots_[i]->getPower());
					delete spaceship_shots_[i];
					spaceship_shots_.erase(spaceship_shots_.begin() + i);
					if (i > 0)
						--i;
					if (asteroids_[j]->getHp() <= 0)
					{
						delete asteroids_[j];
						asteroids_.erase(asteroids_.begin() + j);
						if (j > 0)
							--j;

						player_->addScore(10);
						player_->addMoney(5);
					}
					break;
				}
			}

		}
	}
}