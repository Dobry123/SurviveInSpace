#include "Game.h"

namespace sis
{
	Game::Game()
	{
		this->assets_ = new AssetManager;
		this->scoreboard_ = new Scoreboard;
		this->window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Survive in space", sf::Style::Close);
		loadAssets();
		this->menu_ = new Menu(window_, assets_, scoreboard_);

		loop();
	}

	Game::~Game()
	{
		delete this->assets_;
		delete this->scoreboard_;
	}

	void Game::loadAssets()
	{
		assets_->LoadTexture(MENU_BACKGROUND, MENU_BACKGROUND_FILEPATH);
		assets_->LoadTexture(SCOREBOARD_BACKGROUND, SCOREBOARD_BACKGROUND_FILEPATH);
		assets_->LoadFont(MENU_FONT, MENU_FONT_FILEPATH);
	}

	void Game::loop()
	{
		int result = menu_->processMenu();
		if (result == 3)
			window_->close();
		else
			window_->close(); //temp
	}
}