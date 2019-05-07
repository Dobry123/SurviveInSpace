#include "Game.h"

namespace sis
{
	Game::Game():
		frameRate_(1.0f / FRAME_RATE)
	{
		this->assets_ = new AssetManager;
		this->scoreboard_ = new Scoreboard;
		this->window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Survive in space", sf::Style::Close);
		loadAssets();
		this->menu_ = new Menu(window_, assets_, scoreboard_);
		this->player_ = new Player();
		this->hud_ = new HUD(window_, assets_, player_);
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
		assets_->LoadTexture(ASTEROID_SMALL, ASTEROID_SMALL_FILEPATH);
		assets_->LoadTexture(ASTEROID, ASTEROID_FILEPATH);
		assets_->LoadTexture(SPACESHIP, SPACESHIP_FILEPATH);
		assets_->LoadTexture(SHOT_TYPE_0, SHOT_TYPE_0_FILEPATH);
		assets_->LoadTexture(EXPLOSION_1, EXPLOSION_1_FILEPATH);
		assets_->LoadFont(MENU_FONT, MENU_FONT_FILEPATH);

	}

	void Game::run()
	{
		int result = menu_->process();
		if (result == 3)
			window_->close();
		else
		{
			player_->setName(menu_->inputNameScreen());
			if (player_->getName() == "")
				run();

			//Game loop
			object_manager_ = new ObjectManager(window_, assets_, player_);
			float newTime, currentTime, frameTime;
			float accumulator = 0.0f;
			currentTime = clock_.getElapsedTime().asSeconds();
			while (window_->isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				newTime = clock_.getElapsedTime().asSeconds();
				frameTime = newTime - currentTime;

				currentTime = newTime;
				accumulator += frameTime;

				while (accumulator >= frameRate_)
				{
					// update
					object_manager_->process(frameRate_);
					accumulator -= frameRate_;
				}

				// draw
				window_->clear();
				object_manager_->draw();
				hud_->draw(5);
				window_->display();
			}
			window_->close();
		}
	}
}