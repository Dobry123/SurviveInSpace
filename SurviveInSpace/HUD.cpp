#include "HUD.h"

namespace sis
{
	HUD::HUD(sf::RenderWindow *window, AssetManager *assets, Player *player)
	{
		window_ = window;
		assets_ = assets;
		player_ = player;
		text_.setFont(assets_->getFont(MENU_FONT));
		text_.setCharacterSize(30);
	}

	void HUD::draw(float lvl_time_left)
	{
		std::stringstream ss;
		ss << "Time left: " << lvl_time_left;
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(0, 0));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss.str("");
		ss << "Score: " << player_->getScore();
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(WINDOW_WIDTH	- 200, 0));
		window_->draw(text_);

		ss.str("");
		ss << player_->getMoney() << " PLN";
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 0));
		window_->draw(text_);

		ss.str("");
		ss << "L: " << player_->getLifes();
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(0, WINDOW_HEIGHT - 30));
		window_->draw(text_);
	}
}