#include "AssetManager.h"

namespace sis
{
	AssetManager::AssetManager() { }

	AssetManager::~AssetManager()
	{
		textures_.clear();
		fonts_.clear();
	}

	bool AssetManager::LoadFont(std::string name, std::string name_path)
	{
		sf::Font font;
		if (font.loadFromFile(name_path));
		{
			fonts_[name] = font;
			return true;
		}
		return false;
	}

	bool AssetManager::LoadTexture(std::string name, std::string name_path)
	{
		sf::Texture texture;
		if (texture.loadFromFile(name_path))
		{
			textures_[name] = texture;
			return true;
		}
		return false;
	}

	sf::Font &AssetManager::getFont(std::string name)
	{
		return fonts_.at(name);
	}

	sf::Texture &AssetManager::getTexture(std::string name)
	{
		return textures_.at(name);
	}
}