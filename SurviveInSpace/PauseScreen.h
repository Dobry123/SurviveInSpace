#pragma once
#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include "Menu.h"

namespace sis
{
	class PauseScreen :public Menu
	{
	public:
		PauseScreen(sf::RenderWindow *window, AssetManager *assets, Scoreboard *scoreboard);
	};
}

#endif // !PAUSE_SCREEN_H