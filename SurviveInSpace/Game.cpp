#include "Game.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "Shot.h"

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
		assets_->LoadFont(MENU_FONT, MENU_FONT_FILEPATH);

	}

	void Game::run()
	{
		int result = menu_->process();
		if (result == 3)
			window_->close();
		else
		{
			//Game loop
			Asteroid a(window_, assets_);
			SpaceShip s(window_, assets_);
			std::vector<Shot *> shots;
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
					a.update(frameRate_);
					s.update(frameRate_);
					if (s.ifShot())
					{
						shots.push_back(s.getShots()[0]);
					}
					for (int i = 0; i < shots.size(); ++i)
					{
						if (shots[i]->isDead())
						{
							delete shots[i];
							shots.erase(shots.begin() + i);
						}
						else
							shots[i]->update(frameRate_);
					}
					accumulator -= frameRate_;
				}

				// draw
				window_->clear();
				a.draw();
				s.draw();
				for (int i = 0; i < shots.size(); ++i)
				{
					shots[i]->draw();
				}
				window_->display();
			}
			window_->close();
		}
	}
}