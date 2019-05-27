#include "Level.h"

namespace sis
{
	Level::Level():
		current_level_(1)
	{
		l1_.time = 15;
		l1_.asteroid = 50;
		l1_.asteroid_difficult = 1;

		l2_.time = 30;
		l2_.asteroid = 30;
		l2_.asteroid_difficult = 1;

		l3_.time = 30;
		l3_.asteroid = 30;
		l3_.asteroid_difficult = 1;

		l4_.time = 30;
		l4_.asteroid = 30;
		l4_.asteroid_difficult = 1;

		l5_.time = 30;
		l5_.asteroid = 30;
		l5_.asteroid_difficult = 1;

		l6_.time = 30;
		l6_.asteroid = 30;
		l6_.asteroid_difficult = 1;

		l7_.time = 30;
		l7_.asteroid = 30;
		l7_.asteroid_difficult = 1;
	}

	LevelData Level::getLevelData()
	{
		switch (current_level_)
		{
		case 1:
			return l1_;
		case 2:
			return l2_;
		case 3:
			return l3_;
		case 4:
			return l4_;
		case 5:
			return l5_;
		case 6:
			return l6_;
		case 7:
			return l7_;
		}
	}

	void Level::levelUp()
	{
		++ current_level_;
	}

	int Level::getCurrentLevel()
	{
		return current_level_;
	}
}