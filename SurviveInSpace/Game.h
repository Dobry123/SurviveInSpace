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

	private:
		sf::RenderWindow *window_;
		AssetManager *assets_;
		Scoreboard *scoreboard_;
		Menu *menu_;
		void loadAssets();
		void loop();
	};
}


#endif // !GAME_H