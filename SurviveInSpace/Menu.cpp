#include "Menu.h"

namespace sis
{
	Menu::Menu(sf::RenderWindow *window, AssetManager *assets, Scoreboard *scoreboard) :
		current_choice_(0),
		menuTextsSize_(sizeof(menuTexts_) / sizeof(*menuTexts_)),
		delayTime_(0.15),
		choice_selected_(false)
	{
		menuTexts_[0] = "New Game";
		menuTexts_[1] = "Settings";
		menuTexts_[2] = "Scoreboard";
		menuTexts_[3] = "Exit";

		this->window_ = window;
		this->assets_ = assets;
		this->scoreboard_ = scoreboard;
		backgroundSprite_.setTexture(assets_->getTexture(MENU_BACKGROUND));
		scoreboard_backgroundSprite_.setTexture(assets_->getTexture(SCOREBOARD_BACKGROUND));
		text_.setFont(assets_->getFont(MENU_FONT));
	}

	Menu::~Menu()
	{
	}

	void Menu::handleInput()
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
		}
	}

	void Menu::draw()
	{
		window_->clear();
		window_->draw(backgroundSprite_);

		text_.setCharacterSize(60);
		for (int i = 0; i < menuTextsSize_; ++i)
		{
			text_.setString(menuTexts_[i]);
			text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 7, i * WINDOW_HEIGHT / 8));
			if (current_choice_ == i)
				text_.setFillColor(sf::Color::Yellow);
			else
				text_.setFillColor(sf::Color::White);
			window_->draw(text_);
		}

		window_->display();
	}

	int Menu::process()
	{
		while (!choice_selected_)
		{
			handleInput();
			draw();
		}
		choice_selected_ = false;

		if (current_choice_ == 2)
			showScoreboard();
		return current_choice_;
	}

	void Menu::showScoreboard()
	{
		window_->clear();
		window_->draw(scoreboard_backgroundSprite_);

		text_.setCharacterSize(40);
		for (int i = 0; i < 10; ++i)
		{
			int score;
			std::string name;
			scoreboard_->getRecord(i, name, score);
			std::stringstream ss;
			ss << i + 1 << ".\t" << name << "\t" << score;
			text_.setString(ss.str());
			text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 3, i * WINDOW_HEIGHT / 20));
			if (i % 2 == 0)
				text_.setFillColor(sf::Color::White);
			else
				text_.setFillColor(sf::Color::Yellow);
			window_->draw(text_);
		}
		text_.setString("ESC TO BACK");
		text_.setPosition(sf::Vector2f(10, WINDOW_HEIGHT - 40));
		window_->draw(text_);

		window_->display();
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {}
		process();
	}
}