#include "AssetManager.h"

namespace sis
{
	AssetManager::AssetManager() { }

	AssetManager::~AssetManager()
	{
		this->textures_.clear();
		this->fonts_.clear();
	}

	bool AssetManager::LoadFont(std::string name, std::string name_path)
	{
		sf::Font font;
		if (font.loadFromFile(name_path));
		{
			this->fonts_[name] = font;
			return true;
		}
		return false;
	}

	bool AssetManager::LoadTexture(std::string name, std::string name_path)
	{
		sf::Texture texture;
		if (texture.loadFromFile(name_path))
		{
			this->textures_[name] = texture;
			return true;
		}
		return false;
	}

	sf::Font &AssetManager::getFont(std::string name)
	{
		return this->fonts_.at(name);
	}

	sf::Texture &AssetManager::getTexture(std::string name)
	{
		return this->textures_.at(name);
	}
}