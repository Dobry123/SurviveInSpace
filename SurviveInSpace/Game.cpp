#include "Game.h"

namespace sis
{
	Game::Game():
		frameRate_(1.0f / FRAME_RATE),
		state_(0)
	{
		assets_ = new AssetManager;
		scoreboard_ = new Scoreboard;
		window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Survive in space", sf::Style::Close);
		loadAssets();
		menu_ = new Menu(window_, assets_, scoreboard_);
	}

	Game::~Game()
	{
		delete assets_;
		delete scoreboard_;
		delete window_;
		delete menu_;
		delete player_;
		delete hud_;
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
			if (restartForNewGame())
			{
				if (gameLoop() == 1)
				{
					UpdateScreen *updateScreen = new UpdateScreen(window_, assets_, player_, object_manager_->getSpaceShip());
					updateScreen->process();
					delete updateScreen;
					// update screen
					level_->levelUp();
				}
			}
				
			else
				run();
		}
	}

	int Game::gameLoop()
	{
		float newTime, currentTime, frameTime;
		float accumulator = 0.0f;
		int ob_state = 0;
		currentTime = clock_.getElapsedTime().asSeconds();
		level_clock_.restart();
		while (window_->isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			newTime = clock_.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			currentTime = newTime;
			accumulator += frameTime;

			float time_left = level_->getLevelData().time - level_clock_.getElapsedTime().asSeconds();

			while (accumulator >= frameRate_)
			{
				// update
				ob_state = object_manager_->process(frameRate_, level_->getLevelData());
				accumulator -= frameRate_;
			}

			// draw
			window_->clear();
			object_manager_->draw();
			hud_->draw(time_left);
			window_->display();

			if (time_left <= 0)
			{
				object_manager_->clearEnemyObjects();
				
				return 1; // level end
			}

			if (ob_state == -1)
				return -1; // game end
		}
	}

	bool Game::restartForNewGame()
	{
		delete level_;
		delete player_;
		delete hud_;
		delete object_manager_;

		level_ = new Level();
		state_ = 0;
		player_ = new Player();
		object_manager_ = new ObjectManager(window_, assets_, player_);
		hud_ = new HUD(window_, assets_, player_);

		player_->setName(menu_->inputNameScreen());
		if (player_->getName() == "")
			return false;
		else
			return true;
	}
}