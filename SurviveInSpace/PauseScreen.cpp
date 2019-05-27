#include "PauseScreen.h"

namespace sis
{
	PauseScreen::PauseScreen(sf::RenderWindow *window, AssetManager *assets, Scoreboard *scoreboard) :
		Menu(window, assets, scoreboard)
	{
		menuTexts_[0] = "Resume";
		menuTexts_[1] = "New game";
		menuTexts_[2] = "Scoreboard";
		menuTexts_[3] = "Exit";
	}
}