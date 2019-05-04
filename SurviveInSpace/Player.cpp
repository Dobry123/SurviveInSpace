#include "Player.h"

namespace sis
{
	Player::Player()
	{
		lifes_ = 1;
		money_ = 0;
		score_ = 0;
		name_ = "Default";
	}

	void Player::setName(std::string name)
	{
		name_ = name;
	}

	std::string Player::getName()
	{
		return name_;
	}

	void Player::addLife()
	{
		lifes_++;
	}

	void Player::minusLife()
	{
		lifes_--;
	}

	int Player::getLifes()
	{
		return lifes_;
	}

	void Player::addMoney(int money)
	{
		money_ += money;
	}

	void Player::spendMoney(int money)
	{
		money_ -= money;
	}

	int Player::getMoney()
	{
		return money_;
	}

	void Player::addScore(int score)
	{
		score_ += score;
	}

	int Player::getScore()
	{
		return score_;
	}
}