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

		l2_.time = 20;
		l2_.asteroid = 20;
		l2_.asteroid_difficult = 2;
		l2_.cruiser = 5;
		l2_.cruiser_difficult = 2;
		l2_.boarder = 5;
		l2_.boarder_difficult = 1;

		l3_.time = 20;
		l3_.asteroid = 20;
		l3_.asteroid_difficult = 2;
		l3_.cruiser = 10;
		l3_.cruiser_difficult = 2;
		l3_.boarder = 10;
		l3_.boarder_difficult = 2;

		l4_.time = 20;
		l4_.asteroid = 25;
		l4_.asteroid_difficult = 3;
		l4_.cruiser = 7;
		l4_.cruiser_difficult = 2;
		l4_.boarder = 7;
		l4_.boarder_difficult = 2;

		l5_.time = 20;
		l5_.asteroid = 25;
		l5_.asteroid_difficult = 3;
		l5_.cruiser = 10;
		l5_.cruiser_difficult = 3;
		l5_.boarder = 10;
		l5_.boarder_difficult = 2;

		l6_.time = 20;
		l6_.asteroid = 25;
		l6_.asteroid_difficult = 4;
		l6_.cruiser = 10;
		l6_.cruiser_difficult = 3;
		l6_.boarder = 10;
		l6_.boarder_difficult = 3;

		l7_.time = 9999;
		l7_.asteroid = 10;
		l7_.asteroid_difficult = 3;
		l7_.cruiser = 1;
		l7_.cruiser_difficult = 4;
		l7_.boarder = 1;
		l7_.boarder_difficult = 4;
		l7_.boss1 = true;
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