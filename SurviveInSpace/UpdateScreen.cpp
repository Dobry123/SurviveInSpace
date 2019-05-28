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
		backgroundSprite_.setTexture(assets_->getTexture(UPGRADE_BACKGROUND));

		texts_[0] = "Shot Hz";
		texts_[1] = "Shot Power";
		texts_[2] = "Shot Range";
		texts_[3] = "Shot Speed";
		texts_[4] = "Number of shots";
		texts_[5] = "Hp";

		spaceship_ = spaceship;
		player_ = player;
		text_.setFont(assets_->getFont(MENU_FONT));
		text_.setCharacterSize(60);
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
				// delay
				clock_.restart();
				while(clock_.getElapsedTime().asSeconds() < delayTime_) { }
			}
		}
	}

	void UpdateScreen::draw()
	{
		window_->clear();
		window_->draw(backgroundSprite_);

		std::stringstream ss;
		ss << "Money:  " << player_->getMoney() << " PLN";
		text_.setString(ss.str());
		text_.setFillColor(sf::Color::Yellow);
		text_.setPosition(sf::Vector2f(0, 0));
		window_->draw(text_);

		text_.setFillColor(sf::Color::White);
		text_.setString("Upgrade your ship");
		text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 200, 0));
		window_->draw(text_);

		for (int i = 0; i < menuTextsSize_; ++i)
		{
			ss.str("");
			switch (i)
			{
			case 0:
				ss << "Shot Hz\t\t\t\t\t" << spaceship_->getShotHz() << "\t -50 PLN";
				text_.setString(ss.str());
				break;

			case 1:
				ss << "Shot Power\t\t\t" << spaceship_->getShotPower() << "\t -50 PLN";
				text_.setString(ss.str());
				break;
			case 2:
				ss << "Shot Range\t\t\t" << spaceship_->getShotRange() << "\t -50 PLN";
				text_.setString(ss.str());
				break;
			case 3:
				ss << "Shot Speed\t\t\t" << spaceship_->getShotSpeed() << "\t -50 PLN";
				text_.setString(ss.str());
				break;
			case 4:
				ss << "Number of shots\t\t" << spaceship_->getShotsNumber() << "\t -500 PLN";
				text_.setString(ss.str());
				break;
			case 5:
				ss << "Hp\t\t\t\t\t\t" << spaceship_->getHp() << "\t -50 PLN";
				text_.setString(ss.str());
				break;
			}

			text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 18, (i + 2) * WINDOW_HEIGHT / 10));
			window_->draw(text_);

			if (current_choice_ == i)
			{
				text_.setString(">> ");
				text_.setFillColor(sf::Color::Yellow);
				text_.setPosition(sf::Vector2f(25, (i + 2) * WINDOW_HEIGHT / 10));
				window_->draw(text_);

				text_.setFillColor(sf::Color::White);
			}
		}

		text_.setFillColor(sf::Color::Yellow);
		text_.setString("ESC to continue");
		text_.setPosition(sf::Vector2f(0, WINDOW_HEIGHT - 60));
		window_->draw(text_);

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
		case 4:
			if (player_->getMoney() >= 500)
			{
				if (spaceship_->getShotsNumber() < 4)
				{
					spaceship_->upgradeShotsNumber();
					player_->spendMoney(50);
				}
			}
			break;
		case 5:
			if (player_->getMoney() >= 50)
			{
				spaceship_->addHp();
				player_->spendMoney(50);
			}
			break;
		}

		process();
	}
}