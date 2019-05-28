#include "Game.h"

namespace sis
{
	Game::Game():
		frameRate_(1.0f / FRAME_RATE),
		state_(0)
	{
		assets_ = new AssetManager;
		scoreboard_ = new Scoreboard;
		window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Survive in space", sf::Style::Fullscreen);
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
		assets_->LoadTexture(UPGRADE_BACKGROUND, UPGRADE_BACKGROUND_FILEPATH);
		assets_->LoadTexture(SCOREBOARD_BACKGROUND, SCOREBOARD_BACKGROUND_FILEPATH);
		assets_->LoadTexture(ASTEROID_SMALL, ASTEROID_SMALL_FILEPATH);
		assets_->LoadTexture(ASTEROID, ASTEROID_FILEPATH);
		assets_->LoadTexture(SPACESHIP, SPACESHIP_FILEPATH);
		assets_->LoadTexture(SHOT_TYPE_0, SHOT_TYPE_0_FILEPATH);
		assets_->LoadTexture(SHOT_TYPE_1, SHOT_TYPE_1_FILEPATH);
		assets_->LoadTexture(EXPLOSION_1, EXPLOSION_1_FILEPATH);
		assets_->LoadTexture(CRUISER, CRUISER_FILEPATH);
		assets_->LoadTexture(BOARDER, BOARDER_FILEPATH);
		assets_->LoadTexture(BOSS_1, BOSS_1_FILEPATH);
		assets_->LoadTexture(HUD_EDGE, HUD_EDGE_FILEPATH);
		assets_->LoadTexture(HUD_BLACK, HUD_BLACK_FILEPATH);
		assets_->LoadFont(MENU_FONT, MENU_FONT_FILEPATH);
	}

	void Game::run(bool new_game)
	{
		int result;
		if (new_game)
			result = 0;
		else
			result = menu_->process();
		if (result == 3)
			window_->close();
		else
		{
			if (restartForNewGame())
			{
				while (1)
				{
					int game_loop_state = gameLoop();

					switch (game_loop_state)
					{
					case -1:		// End game
						scoreboard_->addNewScore(player_->getName(), player_->getScore());
						run();
						return;
					case 1:			// New game
						scoreboard_->addNewScore(player_->getName(), player_->getScore());
						run(true);
						return;
					case 3:			// Exit
						scoreboard_->addNewScore(player_->getName(), player_->getScore());
						window_->close();
						return;
					case 99:		// Level end
						// update screen
						UpdateScreen *updateScreen = new UpdateScreen(window_, assets_, player_, object_manager_->getSpaceShip());
						updateScreen->process();
						delete updateScreen;

						level_->levelUp();
						break;
					}
				}
			}
			else
				run();
		}
	}

	int Game::gameLoop()
	{
		object_manager_->restartSpaceShipPosition();
		float newTime, currentTime, frameTime, timeOnPause = 0;
		float accumulator = 0.0f;
		int ob_state = 0;
		currentTime = clock_.getElapsedTime().asSeconds();
		level_clock_.restart();
		while (window_->isOpen())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				float tmp = level_clock_.getElapsedTime().asSeconds();
				PauseScreen *ps = new PauseScreen(window_, assets_, scoreboard_);
				int pause_state = ps->process();
				delete ps;
				if (pause_state != 0)
					return pause_state;

				newTime = clock_.getElapsedTime().asSeconds();
				currentTime = newTime;
				timeOnPause += level_clock_.getElapsedTime().asSeconds() - tmp;
			}
			newTime = clock_.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			currentTime = newTime;
			accumulator += frameTime;
			float time_left = level_->getLevelData().time - level_clock_.getElapsedTime().asSeconds() + timeOnPause;

			while (accumulator >= frameRate_)
			{
				// update
				ob_state = object_manager_->process(frameRate_, level_->getLevelData());
				accumulator -= frameRate_;
			}

			// draw
			window_->clear();
			object_manager_->draw();
			hud_->draw(time_left, level_->getCurrentLevel());
			window_->display();

			if (time_left <= 0 || ob_state == 99)
			{
				object_manager_->clearEnemyObjects();
				
				return 99; // level end
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
		//delete object_manager_;
		
		level_ = new Level();
		state_ = 0;
		player_ = new Player();
		object_manager_ = new ObjectManager(window_, assets_, player_);
		hud_ = new HUD(window_, assets_, player_, object_manager_->getSpaceShip());
		player_->setName(menu_->inputNameScreen());
		if (player_->getName() == "")
			return false;
		else
			return true;
	}
}