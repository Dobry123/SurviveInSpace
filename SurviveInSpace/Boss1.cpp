#include "Boss1.h"

namespace sis
{
	Boss1::Boss1(sf::RenderWindow *window, AssetManager *assets, int difficult) :
		Shotable(window, assets),
		move_reversed_x_(false),
		move_reversed_y_(false)
	{
		std::mt19937 rng(dev_());
		std::uniform_int_distribution<int> intDistHeight(1, WINDOW_HEIGHT / 2);
		std::uniform_real_distribution<float> floatDist0_1(0, 1);

		hp_ = 2000 * difficult;
		pose_.x = WINDOW_WIDTH / 2;
		pose_.y = 100;
		pose_.rotation = 180;
		speed_ = 120 + 50 * floatDist0_1(rng) * difficult;

		sprite_.setTexture(assets_->getTexture(BOSS_1));
		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
		sprite_.setRotation(pose_.rotation);
		sprite_.setOrigin(sf::Vector2f(58, 55));
		sprite_.setScale(sf::Vector2f(3, 3));
		r_ = 46 * sprite_.getScale().x;

		shot_stats_.hz = 1 * difficult;
		shot_stats_.power = 25 * difficult;
		shot_stats_.range = 500 + 50 * difficult;
		shot_stats_.speed = 500 + 25 * difficult;

		last_shot_time_ = clock_.getElapsedTime().asSeconds();
	}

	void Boss1::draw()
	{
		window_->draw(sprite_);
	}

	void Boss1::update(float dt)
	{
		if (did_shot_)
		{
			createdShots_.clear();
			did_shot_ = false;
		}
		shot();
		move(dt);
	}

	void Boss1::move(float dt)
	{
		std::mt19937 rng(dev_());
		std::uniform_int_distribution<int> reversedRandom(1, 200);
		if (reversedRandom(rng) % 199 == 0)
			move_reversed_x_ = !move_reversed_x_;

		if (reversedRandom(rng) % 199 == 0)
			move_reversed_y_ = !move_reversed_y_;

		if (move_reversed_x_)
			pose_.x -= speed_ * dt;
		else
			pose_.x += speed_ * dt;

		if (move_reversed_y_)
			pose_.y -= speed_ * dt;
		else
			pose_.y += speed_ * dt;

		if (pose_.x > GAME_WIDTH_MAX + 100)
		{
			move_reversed_x_ = !move_reversed_x_;
		}

		if (pose_.x < GAME_WIDTH_MIN - 100)
		{
			move_reversed_x_ = !move_reversed_x_;
		}

		if (pose_.y > GAME_HEIGHT + 100)
		{
			move_reversed_y_ = !move_reversed_y_;
		}

		if (pose_.y < -100)
		{
			move_reversed_y_ = !move_reversed_y_;
		}

		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
	}

	void Boss1::shot()
	{
		float time_lasts = clock_.getElapsedTime().asSeconds() - last_shot_time_;
		if (time_lasts > 1 / shot_stats_.hz)
		{
			did_shot_ = true;
			Pose shot_pose = pose_;
			for (int i = 0; i < 360; i+=7)
			{
				shot_pose.rotation = i;
				Shot *shot = new Shot(window_, assets_, shot_pose, shot_stats_, 1);
				createdShots_.push_back(shot);
			}
			last_shot_time_ = clock_.getElapsedTime().asSeconds();
		}
	}
}