#pragma once
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

namespace sis
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		bool LoadTexture(std::string name, std::string name_path);
		bool LoadFont(std::string name, std::string name_path);
		sf::Font &getFont(std::string name);
		sf::Texture &getTexture(std::string name);

	private:
		std::map<std::string, sf::Texture> textures_;
		std::map<std::string, sf::Font> fonts_;
	};
}

#endif // !ASSET_MANAGER_H
