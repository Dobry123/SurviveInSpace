#include "SpaceShip.h"

namespace sis
{
	SpaceShip::SpaceShip(sf::RenderWindow *window, AssetManager *assets) :
		Shotable(window, assets)
	{
		pose_.x = WINDOW_WIDTH / 2;
		pose_.y = WINDOW_HEIGHT / 2;
		pose_.rotation = 0;
		speed_ = 500;
		hp_ = 100;

		sprite_.setTexture(assets_->getTexture(SPACESHIP));
		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
		sprite_.setRotation(pose_.rotation);
		sprite_.setOrigin(sf::Vector2f(19, 18));
		sprite_.setScale(sf::Vector2f(2, 2));
		r_ = 15 * sprite_.getScale().x;
		
		shot_stats_.hz = 15;
		shot_stats_.power = 50;
		shot_stats_.range = 500;
		shot_stats_.speed = 500;

		last_shot_time_ = clock_.getElapsedTime().asSeconds();
	}

	void SpaceShip::draw()
	{
		window_->draw(sprite_);
	}

	void SpaceShip::update(float dt)
	{
		if (did_shot_)
		{
			createdShots_.clear();
			did_shot_ = false;
		}
		shot();
		move(dt);
	}

	void SpaceShip::move(float dt)
	{
		this->sprite_.setTextureRect(sf::IntRect(39, 0, 38, 35));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				this->sprite_.setTextureRect(sf::IntRect(39, 40, 38, 42));
				if (pose_.y > 0 + 20)
				{
					pose_.y -= speed_ * dt;
					sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				this->sprite_.setTextureRect(sf::IntRect(39, 86, 38, 39));
				if (pose_.y < GAME_HEIGHT - 20)
				{
					pose_.y += speed_ * dt;
					sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				this->sprite_.setTextureRect(sf::IntRect(2, 40, 30, 42));
				if (pose_.x > GAME_WIDTH_MIN + 38)
				{
					pose_.x -= speed_ * dt;
					sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				this->sprite_.setTextureRect(sf::IntRect(86, 40, 28, 42));
				if (pose_.x < GAME_WIDTH_MAX - 38)
				{
					pose_.x += speed_ * dt;
					sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
				}
			}

			sf::Vector2f positionSpaceShip = sprite_.getPosition();
			sf::Vector2i positionMouse = sf::Mouse::getPosition(*window_);
			float argArctg = (positionMouse.y - positionSpaceShip.y) / (positionMouse.x - positionSpaceShip.x);
			if (positionMouse.x - positionSpaceShip.x < 0)
				pose_.rotation = atan(argArctg) * 180 / PI - 90;
			else
				pose_.rotation = atan(argArctg) * 180 / PI + 90;

			sprite_.setRotation(pose_.rotation);
	}

	void SpaceShip::shot()
	{
		float time_lasts = clock_.getElapsedTime().asSeconds() - last_shot_time_;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time_lasts > 1 / shot_stats_.hz)
		{
			did_shot_ = true;
			Pose shot_pose = pose_;
			shot_pose.x += sin(pose_.rotation * PI / 180) * 35;
			shot_pose.y += -cos(pose_.rotation * PI / 180) * 35;
			Shot *shot = new Shot(window_, assets_, shot_pose, shot_stats_, 0);
			createdShots_.push_back(shot);
			last_shot_time_ = clock_.getElapsedTime().asSeconds();
		}
	}

	void SpaceShip::setPosition(float x, float y)
	{
		sprite_.setPosition(sf::Vector2f(x, y));
		pose_.y = y;
		pose_.x = x;
	}
}