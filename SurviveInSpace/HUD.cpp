#include "HUD.h"

namespace sis
{
	HUD::HUD(sf::RenderWindow *window, AssetManager *assets, Player *player, SpaceShip *spaceship)
	{
		window_ = window;
		assets_ = assets;
		player_ = player;
		spaceship_ = spaceship;
		text_.setFont(assets_->getFont(MENU_FONT));
		text_.setCharacterSize(30);
		sprite_edge_.setTexture(assets_->getTexture(HUD_EDGE));
		sprite_black_.setTexture(assets_->getTexture(HUD_BLACK));
		sprite_black_.scale(sf::Vector2f(GAME_WIDTH_MIN, GAME_HEIGHT));
	}

	void HUD::draw(float lvl_time_left, int lvl)
	{
		sprite_black_.setPosition(sf::Vector2f(0, 0));
		window_->draw(sprite_black_);
		sprite_black_.setPosition(sf::Vector2f(GAME_WIDTH_MAX, 0));
		window_->draw(sprite_black_);
		sprite_edge_.setPosition(sf::Vector2f(GAME_WIDTH_MIN, 0));
		window_->draw(sprite_edge_);
		sprite_edge_.setPosition(sf::Vector2f(GAME_WIDTH_MAX, 0));
		window_->draw(sprite_edge_);

		std::stringstream ss;

		text_.setString("Level: ");
		text_.setPosition(sf::Vector2f(0, 0));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss << lvl;
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(0, 30));
		text_.setFillColor(sf::Color::White);
		window_->draw(text_);

		text_.setString("Time left: ");
		text_.setPosition(sf::Vector2f(0, 1 * WINDOW_HEIGHT / 5 - 30));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss.str("");
		ss << lvl_time_left;
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(0, 1 * WINDOW_HEIGHT / 5));
		text_.setFillColor(sf::Color::White);
		window_->draw(text_);

		text_.setString("Score: ");
		text_.setPosition(sf::Vector2f(0, 2 * WINDOW_HEIGHT / 5 - 30));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss.str("");
		ss << player_->getScore();
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(0, 2 * WINDOW_HEIGHT / 5));
		text_.setFillColor(sf::Color::White);
		window_->draw(text_);

		text_.setString("Money: ");
		text_.setPosition(sf::Vector2f(0, 3 * WINDOW_HEIGHT / 5 - 30));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss.str("");
		ss << player_->getMoney() << " PLN";
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(0, 3 * WINDOW_HEIGHT / 5));
		text_.setFillColor(sf::Color::White);
		window_->draw(text_);

		text_.setString("Lifes: ");
		text_.setPosition(sf::Vector2f(GAME_WIDTH_MAX + 20, 0));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss.str("");
		ss << player_->getLifes();
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(GAME_WIDTH_MAX + 20, 30));
		text_.setFillColor(sf::Color::White);
		window_->draw(text_);

		text_.setString("Hp: ");
		text_.setPosition(sf::Vector2f(GAME_WIDTH_MAX + 20, 1 * WINDOW_HEIGHT / 5 - 30));
		text_.setFillColor(sf::Color::Yellow);
		window_->draw(text_);

		ss.str("");
		ss << spaceship_->getHp();
		text_.setString(ss.str());
		text_.setPosition(sf::Vector2f(GAME_WIDTH_MAX + 20, 1 * WINDOW_HEIGHT / 5));
		text_.setFillColor(sf::Color::White);
		window_->draw(text_);
	}
}