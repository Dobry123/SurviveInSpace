#pragma once
#ifndef GAME_H
#define GAME_H

#include "AssetManager.h"
#include "Scoreboard.h"
#include "Menu.h"
#include "DEFINITIONS.h"

namespace sis
{
	class Game
	{
	public:
		Game();
		~Game();
		void run();

	private:
		sf::RenderWindow *window_;
		sf::Clock clock_;
		float frameRate_;
		AssetManager *assets_;
		Scoreboard *scoreboard_;
		Menu *menu_;
		void loadAssets();
	};
}


#endif // !GAME_H