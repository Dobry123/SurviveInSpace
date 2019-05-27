#pragma once
#ifndef GAME_H
#define GAME_H

#include "AssetManager.h"
#include "Scoreboard.h"
#include "Menu.h"
#include "ObjectManager.h"
#include "DEFINITIONS.h"
#include "Player.h"
#include "HUD.h"
#include "Level.h"
#include "UpdateScreen.h"

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
		sf::Clock level_clock_;
		float frameRate_;
		AssetManager *assets_;
		Scoreboard *scoreboard_;
		ObjectManager *object_manager_;
		Menu *menu_;
		Player *player_;
		HUD *hud_;
		Level *level_;
		int state_;
		void loadAssets();
		int gameLoop();
		bool restartForNewGame();
	};
}


#endif // !GAME_H