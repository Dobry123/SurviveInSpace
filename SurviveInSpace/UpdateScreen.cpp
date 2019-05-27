#include "UpdateScreen.h"

namespace sis
{
	UpdateScreen::UpdateScreen(sf::RenderWindow *window, AssetManager *assets, Player *player, SpaceShip *spaceship) :
		current_choice_(0),
		menuTextsSize_(sizeof(texts_) / sizeof(*texts_)),
		delayTime_(0.15),
		choice_selected_(false)
	{
		window_ = window;
		assets_ = assets;
		backgroundSprite_.setTexture(assets_->getTexture(MENU_BACKGROUND));

		texts_[0] = "Hz";
		texts_[1] = "Power";
		texts_[2] = "Range";
		texts_[3] = "Speed";

		window_ = window;
		assets_ = assets;
		spaceship_ = spaceship;
		player_ = player;
		backgroundSprite_.setTexture(assets_->getTexture(MENU_BACKGROUND));
		text_.setFont(assets_->getFont(MENU_FONT));
	}

	void UpdateScreen::handleInput()
	{
		sf::Event event;
		while (window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				current_choice_ = 3;
				choice_selected_ = true;
			}

			if (clock_.getElapsedTime().asSeconds() < delayTime_)
				return;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (current_choice_ > 0)
					--current_choice_;
				clock_.restart();
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (current_choice_ < menuTextsSize_ - 1)
					++current_choice_;
				clock_.restart();
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				choice_selected_ = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				choice_selected_ = true;
				current_choice_ = -1;
			}
		}
	}

	void UpdateScreen::draw()
	{
		window_->clear();
		window_->draw(backgroundSprite_);

		text_.setCharacterSize(60);

		std::stringstream ss;
		ss << "Money:  " << player_->getMoney() << " PLN";
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(6 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8));
		window_->draw(text_);
		for (int i = 0; i < menuTextsSize_; ++i)
		{
			ss.str("");
			switch (i)
			{
			case 0:
				ss << "Hz\t\t" << spaceship_->getShotHz();
				text_.setString(ss.str());
				break;

			case 1:
				ss << "Power\t\t" << spaceship_->getShotPower();
				text_.setString(ss.str());
				break;
			case 2:
				ss << "Range\t\t" << spaceship_->getShotRange();
				text_.setString(ss.str());
				break;
			case 3:
				ss << "Speed\t\t" << spaceship_->getShotSpeed();
				text_.setString(ss.str());
				break;
			}

			text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 7, i * WINDOW_HEIGHT / 8));
			window_->draw(text_);

			if (current_choice_ == i)
			{
				text_.setString(">> ");
				text_.setFillColor(sf::Color::Yellow);
				text_.setPosition(sf::Vector2f(200, i * WINDOW_HEIGHT / 8));
				window_->draw(text_);

				text_.setFillColor(sf::Color::White);
			}
		}

		window_->display();
	}

	void UpdateScreen::process()
	{
		while (!choice_selected_)
		{
			handleInput();
			draw();
		}
		choice_selected_ = false;

		if (current_choice_ == -1)
			return;

		switch (current_choice_)
		{
		case 0:
			if (player_->getMoney() >= 50)
			{
				spaceship_->upgradeShotHz();
				player_->spendMoney(50);
			}
			break;

		case 1:
			if (player_->getMoney() >= 50)
			{
				spaceship_->upgradeShotPower();
				player_->spendMoney(50);
			}
			break;
		case 2:
			if (player_->getMoney() >= 50)
			{
				spaceship_->upgradeShotRange();
				player_->spendMoney(50);
			}
			break;
		case 3:
			if (player_->getMoney() >= 50)
			{
				spaceship_->upgradeShotSpeed();
				player_->spendMoney(50);
			}
			break;
		}

		process();
	}
}