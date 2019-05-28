#include "CruiserEnemy.h"

namespace sis
{
	CruiserEnemy::CruiserEnemy(sf::RenderWindow *window, AssetManager *assets, int difficult) :
		Shotable(window, assets),
		move_reversed_(false)
	{
		std::mt19937 rng(dev_());
		std::uniform_int_distribution<int> intDistHeight(1, WINDOW_HEIGHT / 2);
		std::uniform_real_distribution<float> floatDist0_1(0, 1);

		hp_ = 50 * difficult;
		pose_.x = 0;
		pose_.y = intDistHeight(rng);
		pose_.rotation = 180;
		speed_ = 120 + 50 * floatDist0_1(rng) * difficult;

		sprite_.setTexture(assets_->getTexture(CRUISER));
		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
		sprite_.setRotation(pose_.rotation);
		sprite_.setOrigin(sf::Vector2f(19, 18));
		sprite_.setScale(sf::Vector2f(2, 2));
		r_ = 15 * sprite_.getScale().x;

		shot_stats_.hz = 1 * difficult;
		shot_stats_.power = 25 * difficult;
		shot_stats_.range = 500 + 50 * difficult;
		shot_stats_.speed = 500 + 25 * difficult;

		last_shot_time_ = clock_.getElapsedTime().asSeconds();
	}

	void CruiserEnemy::draw()
	{
		window_->draw(sprite_);
	}

	void CruiserEnemy::update(float dt)
	{
		if (did_shot_)
		{
			createdShots_.clear();
			did_shot_ = false;
		}
		shot();
		move(dt);
	}

	void CruiserEnemy::move(float dt)
	{
		std::mt19937 rng(dev_());
		std::uniform_int_distribution<int> reversedRandom(1, 200);
		if (reversedRandom(rng) % 199 == 0)
			if(move_reversed_)
				move_reversed_ = false;
			else
				move_reversed_ = true;

		if(move_reversed_)
			pose_.x -= speed_ * dt;
		else
			pose_.x += speed_ * dt;

		if (pose_.x > GAME_WIDTH_MAX + 30)
		{
			sprite_.setPosition(sf::Vector2f(GAME_WIDTH_MIN -30, pose_.y));
			pose_.x = GAME_WIDTH_MIN -30;
		}

		if (pose_.x < GAME_WIDTH_MIN -30)
		{
			sprite_.setPosition(sf::Vector2f(GAME_WIDTH_MAX + 30, pose_.y));
			pose_.x = GAME_WIDTH_MAX + 30;
		}

		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
	}

	void CruiserEnemy::shot()
	{
		float time_lasts = clock_.getElapsedTime().asSeconds() - last_shot_time_;
		if (time_lasts > 1 / shot_stats_.hz)
		{
			did_shot_ = true;
			Pose shot_pose = pose_;
			shot_pose.y += 35;
			Shot *shot = new Shot(window_, assets_, shot_pose, shot_stats_, 1);
			createdShots_.push_back(shot);
			last_shot_time_ = clock_.getElapsedTime().asSeconds();
		}
	}
}