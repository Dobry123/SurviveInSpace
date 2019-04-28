#include "Asteroid.h"

namespace sis
{
	Asteroid::Asteroid(sf::RenderWindow *window, AssetManager *assets):
		animation_counter_(0)
	{
		this->window_ = window;
		this->assets_ = assets;
		
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> intDistWidth(1, WINDOW_WIDTH);
		std::uniform_real_distribution<float> floatDist0_1(0, 1);

		rotation_ = 360 * floatDist0_1(rng);
		speed_ = 10 * floatDist0_1(rng);
		animation_speed_ = speed_ / 10;

		if (intDistWidth(rng) % 2 == 0)
			sprite_.setTexture(assets_->getTexture(ASTEROID));
		else
			sprite_.setTexture(assets_->getTexture(ASTEROID_SMALL));

		x_ = intDistWidth(rng);
		y_ = 0;
		sprite_.setPosition(sf::Vector2f(x_, y_));
	}

	void Asteroid::update(float dt)
	{
		this->move(dt);
		this->animate();
	}

	void Asteroid::move(float dt)
	{
		float dx = cos(rotation_ * PI / 180) * speed_;
		float dy = -sin(rotation_ * PI / 180) * speed_;
		x_ += dx;
		y_ += dy;
		sprite_.move(sf::Vector2f(dx, dy));

		if (x_ > WINDOW_WIDTH + 30)
		{
			sprite_.setPosition(sf::Vector2f(0, y_));
			x_ = -30;
		}
		if (x_ < -30)
		{
			sprite_.setPosition(sf::Vector2f(WINDOW_WIDTH, y_));
			x_ = WINDOW_WIDTH + 30;
		}
		if (y_ < -30)
		{
			sprite_.setPosition(sf::Vector2f(x_, WINDOW_HEIGHT));
			y_ = WINDOW_HEIGHT + 30;
		}
		if (y_ > WINDOW_HEIGHT + 30)
		{
			sprite_.setPosition(sf::Vector2f(x_, 0));
			y_ = -30;
		}
	}

	void Asteroid::draw()
	{
		this->window_->draw(sprite_);
	}

	void Asteroid::animate()
	{
		if (animation_counter_ >= 15)
			animation_counter_ = 0;
		else
			animation_counter_ += animation_speed_;
		sprite_.setTextureRect(sf::IntRect(64 * int(animation_counter_), 0, 64, 64));
	}
}