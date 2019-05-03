#include "Shot.h"

namespace sis
{
	Shot::Shot(sf::RenderWindow *window, AssetManager *assets, Pose pose, ShotStats stats, int type) :
		toDestroy_(false)
	{
		this->window_ = window;
		this->assets_ = assets;
		pose_ = pose;
		stats_ = stats;
		dx_ = cos(pose_.rotation * PI / 180);
		dy_ = -sin(pose_.rotation * PI / 180);

		switch (type)
		{
		case 0:
			sprite_.setTexture(assets_->getTexture(SHOT_TYPE_0));
		}
		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
	}

	void Shot::move(float dt)
	{
		if (distance_ < stats_.range)
		{
			float dx = dx_ * speed_ * dt;
			float dy = dy_ * speed_ * dt;
			pose_.x += dx;
			pose_.y += dy;
			sprite_.move(sf::Vector2f(dx, dy));
		}
		else
			toDestroy_ = true;
	}

	bool Shot::isDead()
	{
		return toDestroy_;
	}

	void Shot::update(float dt)
	{
		move(dt);
	}

	void Shot::draw()
	{
		window_->draw(sprite_);
	}
}