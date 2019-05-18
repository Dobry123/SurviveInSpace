#include "Scoreboard.h"

namespace sis
{
	Scoreboard::Scoreboard()
	{
		file_.open("Data/scoreboard.txt", std::ios::in | std::ios::out);
		if (file_.good())
		{
			loadScoreboard();
		}
		else
		{
			file_.open("Data/scoreboard.txt", std::ios::in | std::ios::out | std::fstream::trunc);
			for (int i = 0; i < 10; ++i)
			{
				list_[i].place = i + 1;
				list_[i].name = "---";
				list_[i].score = 0;
			}
			saveScoreboard();
		}
	}

	Scoreboard::~Scoreboard()
	{
		saveScoreboard();
		file_.close();
	}

	void Scoreboard::loadScoreboard()
	{
		int record_number = 0;
		while (!file_.eof() && record_number < 10)
		{
			file_ >> list_[record_number].place;
			file_ >> list_[record_number].name;
			file_ >> list_[record_number].score;
			++record_number;
		}
		if (record_number != 10)
		{
			while (record_number != 10)
			{
				list_[record_number].place = record_number + 1;
				list_[record_number].name = "---";
				list_[record_number].score = 0;
				++record_number;
			}
		}
	}

	void Scoreboard::saveScoreboard()
	{
		file_.close();
		file_.open("Data/scoreboard.txt", std::ios::in | std::ios::out | std::fstream::trunc);
		for (int i = 0; i < 10; ++i)
		{
			file_ << list_[i].place;
			file_ << " ";
			file_ << list_[i].name;
			file_ << " ";
			file_ << list_[i].score;
			file_ << "\n";
		}
	}

	void Scoreboard::addNewScore(std::string name, int score)
	{
		int pos = -1;
		for (int i = 0; i < 10; ++i)
		{
			if (list_[i].score < score)
			{
				pos = i;
				break;
			}
		}

		if (pos > -1)
		{
			for (int i = 9; i > pos; --i)
			{
				list_[i].score = list_[i - 1].score;
				list_[i].name = list_[i - 1].name;
			}
			list_[pos].score = score;
			list_[pos].name = name;
		}
	}

	void Scoreboard::getRecord(int place, std::string &n, int &s)
	{
		n = list_[place].name;
		s = list_[place].score;
	}
}