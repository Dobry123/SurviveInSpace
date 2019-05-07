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
		ObjectManager *object_manager_;
		Menu *menu_;
		Player *player_;
		HUD *hud_;
		int state_;
		void loadAssets();
	};
}


#endif // !GAME_H