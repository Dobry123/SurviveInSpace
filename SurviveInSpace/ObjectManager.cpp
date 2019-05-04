#include "ObjectManager.h"

namespace sis
{
	ObjectManager::ObjectManager(sf::RenderWindow *window, AssetManager *assets)
	{
		window_ = window;
		assets_ = assets;

		spaceship_ = new SpaceShip(window_, assets_);
	}

	ObjectManager::~ObjectManager()
	{
		delete spaceship_;
	}

	void ObjectManager::process(float dt)
	{
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
			}
			else
				spaceship_shots_[i]->update(dt);
		}
	}
}