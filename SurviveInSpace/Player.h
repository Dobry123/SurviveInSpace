#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace sis
{
	class Player
	{
	public:
		Player();
		void setName(std::string name);
		std::string getName();
		void addMoney(int money);
		void spendMoney(int money);
		int getMoney();
		void addLife();
		void minusLife();
		int getLifes();
		void addScore(int score);
		int getScore();
	private:
		int money_;
		int lifes_;
		int score_;
		std::string name_;
	};
}

#endif // !PLAYER_H
