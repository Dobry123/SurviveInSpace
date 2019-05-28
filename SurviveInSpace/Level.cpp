#include "Level.h"

namespace sis
{
	Level::Level():
		current_level_(1)
	{
		l1_.time = 20;
		l1_.asteroid = 30;
		l1_.asteroid_difficult = 1;
		l1_.cruiser = 2;
		l1_.cruiser_difficult = 1;
		l1_.boarder = 2;
		l1_.boarder_difficult = 1;

		l2_.time = 15;
		l2_.asteroid = 30;
		l2_.asteroid_difficult = 5;
		l2_.cruiser = 2;
		l2_.cruiser_difficult = 1;
		l2_.boarder = 2;
		l2_.boarder_difficult = 1;

		l3_.time = 15;
		l3_.asteroid = 30;
		l3_.asteroid_difficult = 1;
		l3_.cruiser = 2;
		l3_.cruiser_difficult = 1;
		l3_.boarder = 2;
		l3_.boarder_difficult = 1;

		l4_.time = 30;
		l4_.asteroid = 30;
		l4_.asteroid_difficult = 1;
		l4_.cruiser = 2;
		l4_.cruiser_difficult = 1;
		l4_.boarder = 2;
		l4_.boarder_difficult = 1;

		l5_.time = 30;
		l5_.asteroid = 30;
		l5_.asteroid_difficult = 1;
		l5_.cruiser = 2;
		l5_.cruiser_difficult = 1;
		l5_.boarder = 2;
		l5_.boarder_difficult = 1;

		l6_.time = 30;
		l6_.asteroid = 30;
		l6_.asteroid_difficult = 1;
		l6_.cruiser = 2;
		l6_.cruiser_difficult = 1;
		l6_.boarder = 2;
		l6_.boarder_difficult = 1;

		l7_.time = 30;
		l7_.asteroid = 30;
		l7_.asteroid_difficult = 1;
		l7_.cruiser = 2;
		l7_.cruiser_difficult = 1;
		l7_.boarder = 2;
		l7_.boarder_difficult = 1;
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