#pragma once
#ifndef LEVEL_H
#define LEVEL_H

namespace sis
{
	struct LevelData
	{
		float time; // in seconds
		int asteroid;
		int asteroid_difficult;
	};

	class Level
	{
	public:
		Level();
		LevelData getLevelData();
		void levelUp();
		int getCurrentLevel();
	private:
		int current_level_;
		LevelData l1_;
		LevelData l2_;
		LevelData l3_;
		LevelData l4_;
		LevelData l5_;
		LevelData l6_;
		LevelData l7_;
	};
}

#endif // !LEVEL_H