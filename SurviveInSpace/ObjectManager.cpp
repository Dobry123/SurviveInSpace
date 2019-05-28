#include "ObjectManager.h"

namespace sis
{
	ObjectManager::ObjectManager(sf::RenderWindow *window, AssetManager *assets, Player *player)
	{
		window_ = window;
		assets_ = assets;
		player_ = player;

		spaceship_ = new SpaceShip(window_, assets_);
		cruisers_amount_ = 0;
		boarders_amount_ = 0;
	}

	ObjectManager::~ObjectManager()
	{
		clearEnemyObjects();
		delete spaceship_;
	}

	int ObjectManager::process(float dt, LevelData lvl_data)
	{
		if (player_->getLifes() > 0)
		{
			checkCollisions();

			// update spaceship
			spaceship_->update(dt);
		}
		else if (explosions_.empty())
		{
			clearEnemyObjects();
			delete spaceship_;
			return -1; // end game
		}

		processShots(dt);

		// spawn asteroids
		if (asteroids_.size() < lvl_data.asteroid)
		{
			int spawn = lvl_data.asteroid - asteroids_.size();
			for (int i = 0; i < spawn; ++i)
				asteroids_.push_back(new Asteroid(window_, assets_, lvl_data.asteroid_difficult));
		}

		// spawn cruisers
		if (cruisers_amount_ < lvl_data.cruiser)
		{
			int spawn = lvl_data.cruiser - cruisers_amount_;
			for (int i = 0; i < spawn; ++i)
			{
				enemies_.push_back(new CruiserEnemy(window_, assets_, lvl_data.cruiser_difficult));
				++cruisers_amount_;
			}
		}

		// spawn boarders
		if (boarders_amount_ < lvl_data.boarder)
		{
			int spawn = lvl_data.boarder - boarders_amount_;
			for (int i = 0; i < spawn; ++i)
			{
				enemies_.push_back(new BoarderEnemy(window_, assets_, lvl_data.boarder_difficult));
				++boarders_amount_;
			}
		}

		// update asteroids
		for (int i = 0; i < asteroids_.size(); ++i)
		{
			asteroids_[i]->update(dt);
		}

		// update enemies
		for (int i = 0; i < enemies_.size(); ++i)
		{
			enemies_[i]->update(dt);
		}

		// update explosions
		for (int i = 0; i < explosions_.size(); ++i)
		{
			if (explosions_[i]->isEnd())
			{
				delete explosions_[i];
				explosions_.erase(explosions_.begin() + i);
				if (i > 0)
					--i;
			}
			else
				explosions_[i]->update(dt);
		}
		return 0;
	}

	void ObjectManager::draw()
	{
		if(player_->getLifes() > 0)
			spaceship_->draw();

		for (int i = 0; i < asteroids_.size(); ++i)
		{
			asteroids_[i]->draw();
		}

		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			spaceship_shots_[i]->draw();
		}

		for (int i = 0; i < explosions_.size(); ++i)
		{
			explosions_[i]->draw();
		}

		for (int i = 0; i < enemies_.size(); ++i)
		{
			enemies_[i]->draw();
		}

		for (int i = 0; i < enemy_shots_.size(); ++i)
		{
			enemy_shots_[i]->draw();
		}
	}

	void ObjectManager::processShots(float dt)
	{
		// crate new spaceship shots
		if (spaceship_->ifShot())
		{
			spaceship_shots_.push_back(spaceship_->getShots()[0]);
		}

		// crate new enemies shots
		for (int i = 0; i < enemies_.size(); ++i)
		{
			if (enemies_[i]->ifShot())
			{
				enemy_shots_.push_back(enemies_[i]->getShots()[0]);
			}
		}

		// update spaceship shots
		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			if (spaceship_shots_[i]->isDead())
			{
				delete spaceship_shots_[i];
				spaceship_shots_.erase(spaceship_shots_.begin() + i);
				if (i > -1)
					--i;
			}
			else
				spaceship_shots_[i]->update(dt);
		}

		// update enemies shots
		for (int i = 0; i < enemy_shots_.size(); ++i)
		{
			if (enemy_shots_[i]->isDead())
			{
				delete enemy_shots_[i];
				enemy_shots_.erase(enemy_shots_.begin() + i);
				if (i > -1)
					--i;
			}
			else
				enemy_shots_[i]->update(dt);
		}
	}

	void ObjectManager::checkCollisions()
	{
		// check spaceship shots and asteroids
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
					if (i > -1)
						--i;
					if (asteroids_[j]->getHp() <= 0)
					{
						explosions_.push_back(new Explosion(window_, assets_, asteroids_[j]->getPose()));

						delete asteroids_[j];
						asteroids_.erase(asteroids_.begin() + j);
						if (j > -1)
							--j;

						player_->addScore(10);
						player_->addMoney(5);
					}
					break;
				}
			}
		}

		// check collsion spaceship and asteroids
		for (int i = 0; i < asteroids_.size(); ++i)
		{
			float d = std::sqrtf((asteroids_[i]->getPose().x - spaceship_->getPose().x)
				* (asteroids_[i]->getPose().x - spaceship_->getPose().x)
				+ (asteroids_[i]->getPose().y - spaceship_->getPose().y)
				* (asteroids_[i]->getPose().y - spaceship_->getPose().y));

			if (d < asteroids_[i]->getR() + spaceship_->getR())
			{
				spaceship_->hit(spaceship_->getHp());
				explosions_.push_back(new Explosion(window_, assets_, spaceship_->getPose()));
				player_->minusLife();
			}
		}

		// check collsion spaceship and enemies
		for (int i = 0; i < enemies_.size(); ++i)
		{
			float d = std::sqrtf((enemies_[i]->getPose().x - spaceship_->getPose().x)
				* (enemies_[i]->getPose().x - spaceship_->getPose().x)
				+ (enemies_[i]->getPose().y - spaceship_->getPose().y)
				* (enemies_[i]->getPose().y - spaceship_->getPose().y));

			if (d < enemies_[i]->getR() + spaceship_->getR())
			{
				spaceship_->hit(spaceship_->getHp());
				explosions_.push_back(new Explosion(window_, assets_, spaceship_->getPose()));
				player_->minusLife();
			}
		}

		// check enemy shots and spaceship
		for (int i = 0; i < enemy_shots_.size(); ++i)
		{
			float d = std::sqrtf((enemy_shots_[i]->getPose().x - spaceship_->getPose().x)
				* (enemy_shots_[i]->getPose().x - spaceship_->getPose().x)
				+ (enemy_shots_[i]->getPose().y - spaceship_->getPose().y)
				* (enemy_shots_[i]->getPose().y - spaceship_->getPose().y));
			if (d < enemy_shots_[i]->getR() + spaceship_->getR())
			{
				spaceship_->hit(enemy_shots_[i]->getPower());
				delete enemy_shots_[i];
				enemy_shots_.erase(enemy_shots_.begin() + i);
				if (i > -1)
					--i;
				if (spaceship_->getHp() <= 0)
				{
					explosions_.push_back(new Explosion(window_, assets_, spaceship_->getPose()));
					player_->minusLife();
				}
				break;
			}
		}

		// check spaceship shots and enemies
		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			for (int j = 0; j < enemies_.size(); ++j)
			{
				float d = std::sqrtf((spaceship_shots_[i]->getPose().x - enemies_[j]->getPose().x)
					* (spaceship_shots_[i]->getPose().x - enemies_[j]->getPose().x)
					+ (spaceship_shots_[i]->getPose().y - enemies_[j]->getPose().y)
					* (spaceship_shots_[i]->getPose().y - enemies_[j]->getPose().y));
				if (d < spaceship_shots_[i]->getR() + enemies_[j]->getR())
				{
					enemies_[j]->hit(spaceship_shots_[i]->getPower());
					delete spaceship_shots_[i];
					spaceship_shots_.erase(spaceship_shots_.begin() + i);
					if (i > -1)
						--i;
					if (enemies_[j]->getHp() <= 0)
					{
						explosions_.push_back(new Explosion(window_, assets_, enemies_[j]->getPose()));

						if (enemies_[j]->getType() == 1)
							--cruisers_amount_;
						else if(enemies_[j]->getType() == 2)
							--boarders_amount_;
						delete enemies_[j];
						enemies_.erase(enemies_.begin() + j);
						if (j > -1)
							--j;

						player_->addScore(10);
						player_->addMoney(5);
					}
					break;
				}
			}
		}
	}
	
	void ObjectManager::clearEnemyObjects()
	{
		for (int i = 0; i < asteroids_.size(); ++i)
		{
			delete asteroids_[i];
			asteroids_.erase(asteroids_.begin() + i);
			if (i > -1)
				--i;
		}

		for (int i = 0; i < spaceship_shots_.size(); ++i)
		{
			delete spaceship_shots_[i];
			spaceship_shots_.erase(spaceship_shots_.begin() + i);
			if (i > -1)
				--i;
		}

		for (int i = 0; i < enemies_.size(); ++i)
		{
			delete enemies_[i];
			enemies_.erase(enemies_.begin() + i);
			if (i > -1)
				--i;
		}

		for (int i = 0; i < enemy_shots_.size(); ++i)
		{
			delete enemy_shots_[i];
			enemy_shots_.erase(enemy_shots_.begin() + i);
			if (i > -1)
				--i;
		}
	}

	void ObjectManager::restartSpaceShipPosition()
	{
		spaceship_->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
}