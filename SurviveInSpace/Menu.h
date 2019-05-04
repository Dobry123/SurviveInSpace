#pragma once
#ifndef MENU_H
#define MENU_H

#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Scoreboard.h"
#include "DEFINITIONS.h"

namespace sis
{
	class Menu
	{
	public:
		Menu(sf::RenderWindow *window, AssetManager *assets, Scoreboard *scoreboard);
		~Menu();
		int process();
		std::string inputNameScreen();

	private:
		sf::RenderWindow *window_;
		AssetManager *assets_;
		Scoreboard *scoreboard_;
		sf::Sprite backgroundSprite_;
		sf::Sprite scoreboard_backgroundSprite_;
		float delayTime_;
		sf::Clock clock_;
		std::string menuTexts_[4];
		sf::Text text_;
		int menuTextsSize_;
		int current_choice_;
		bool choice_selected_;

		void handleInput();
		void draw();
		void showScoreboard();
	};
}

#endif // !MENU_H