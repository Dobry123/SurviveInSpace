#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "DEFINITIONS.h"

namespace sis
{
	class Object
	{
	public:
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
	protected:
		float x_, y_;
		float rotation_;
		float speed_;
		int hp_;
		sf::RenderWindow *window_;
		sf::Sprite sprite_;
		AssetManager *assets_;

		virtual void move(float dt) = 0;
	};
}

#endif // !OBJECT_H