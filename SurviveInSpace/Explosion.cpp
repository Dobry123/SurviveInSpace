#include "Explosion.h"

namespace sis
{
	Explosion::Explosion(sf::RenderWindow *window, AssetManager *assets, Pose pose):
		end_(false),
		animation_counter_(0)
	{
		this->window_ = window;
		this->assets_ = assets;
		pose_ = pose;
		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
		sprite_.setOrigin(sf::Vector2f(25, 25));

		animation_speed_ = 0.5;

		sprite_.setTexture(assets_->getTexture(EXPLOSION_1));
		sprite_.setTextureRect(sf::IntRect(0, 0, 50, 50));
	}

	void Explosion::draw()
	{
		this->window_->draw(sprite_);
	}

	void Explosion::update(float dt)
	{
		animate();
	}

	void Explosion::animate()
	{
		if (animation_counter_ >= 19)
			end_ = true;
		else
			animation_counter_ += animation_speed_;
		sprite_.setTextureRect(sf::IntRect(50 * int(animation_counter_), 0, 50, 50));
	}

	bool Explosion::isEnd()
	{
		return end_;
	}

	void Explosion::move(float dt)
	{
		;
	}
}