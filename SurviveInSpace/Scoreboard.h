#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <fstream>
#include <string>

namespace sis
{
	struct Record
	{
		int place;
		std::string name;
		int score;
	};

	class Scoreboard
	{
	public:
		Scoreboard();
		~Scoreboard();
		void addNewScore(std::string name, int score);

	private:
		Record list_[10];
		std::fstream file_;
		void saveScoreboard();
		void loadScoreboard();
	};
}

#endif // !SCOREBOARD_H
