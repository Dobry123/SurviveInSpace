#include "Scoreboard.h"

namespace sis
{
	Scoreboard::Scoreboard()
	{
		this->file_.open("Data/scoreboard.txt", std::ios::in | std::ios::out);
		if (file_.good())
		{
			this->loadScoreboard();
		}
		else
		{
			this->file_.open("Data/scoreboard.txt", std::ios::in | std::ios::out | std::fstream::trunc);
			for (int i = 0; i < 10; ++i)
			{
				this->list_[i].place = i + 1;
				this->list_[i].name = "---";
				this->list_[i].score = 0;
			}
			this->saveScoreboard();
		}
	}

	Scoreboard::~Scoreboard()
	{
		this->saveScoreboard();
		this->file_.close();
	}

	void Scoreboard::loadScoreboard()
	{
		int record_number = 0;
		while (!this->file_.eof() && record_number < 10)
		{
			this->file_ >> this->list_[record_number].place;
			this->file_ >> this->list_[record_number].name;
			this->file_ >> this->list_[record_number].score;
			++record_number;
		}
		if (record_number != 10)
		{
			while (record_number != 10)
			{
				this->list_[record_number].place = record_number + 1;
				this->list_[record_number].name = "---";
				this->list_[record_number].score = 0;
				++record_number;
			}
		}
	}

	void Scoreboard::saveScoreboard()
	{
		this->file_.close();
		this->file_.open("Data/scoreboard.txt", std::ios::in | std::ios::out | std::fstream::trunc);
		for (int i = 0; i < 10; ++i)
		{
			this->file_ << this->list_[i].place;
			this->file_ << " ";
			this->file_ << this->list_[i].name;
			this->file_ << " ";
			this->file_ << this->list_[i].score;
			this->file_ << "\n";
		}
	}

	void Scoreboard::addNewScore(std::string name, int score)
	{
		int pos = -1;
		for (int i = 0; i < 10; ++i)
		{
			if (this->list_[i].score < score)
			{
				pos = i;
				break;
			}
		}

		if (pos > -1)
		{
			for (int i = 9; i > pos; --i)
			{
				this->list_[i].score = this->list_[i - 1].score;
				this->list_[i].name = this->list_[i - 1].name;
			}
			this->list_[pos].score = score;
			this->list_[pos].name = name;
		}
	}
}