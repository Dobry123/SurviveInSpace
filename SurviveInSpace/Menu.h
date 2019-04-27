#pragma once
#ifndef MENU_H
#define MENU_H

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
		Menu(sf::RenderWindow *window, AssetManager *assets);
		~Menu();
		int processMenu();

	private:
		sf::RenderWindow *window_;
		AssetManager *assets_;
		sf::Sprite backgroundSprite_;
		float delayTime_;
		sf::Clock clock_;
		std::string menuTexts_[4];
		sf::Text text_;
		int menuTextsSize_;
		int current_choice_;
		bool choice_selected_;

		void handleInput();
		void draw();
	};
}

#endif // !MENU_H