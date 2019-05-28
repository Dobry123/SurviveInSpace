#pragma once
#ifndef HUD_H
#define HUD_H

#include "Player.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>

namespace sis
{
	class HUD
	{
	public:
		HUD(sf::RenderWindow *window, AssetManager *assets, Player *player);
		void draw(float lvl_time_left, int lvl);
	private:
		sf::RenderWindow *window_;
		AssetManager *assets_;
		Player *player_;
		sf::Text text_;
		sf::Sprite sprite_edge_;
		sf::Sprite sprite_black_;
	};
}

#endif // !HUD_H
