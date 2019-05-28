#pragma once
#ifndef UPDATE_SCREEN_H
#define UPDATE_SCREEN_H

#include "AssetManager.h"
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>
#include "Player.h"
#include "SpaceShip.h"

namespace sis
{
	class UpdateScreen
	{
	public:
		UpdateScreen(sf::RenderWindow *window, AssetManager *assets, Player *player, SpaceShip *spaceship);
		void process();

	private:
		sf::RenderWindow *window_;
		AssetManager *assets_;
		Player *player_;
		SpaceShip *spaceship_;

		sf::Sprite backgroundSprite_;
		float delayTime_;
		sf::Clock clock_;
		sf::Text text_;
		int menuTextsSize_;
		int current_choice_;
		bool choice_selected_;
		std::string texts_[6];

		void handleInput();
		void draw();
	};
}

#endif // !UPDATE_SCREEN_H