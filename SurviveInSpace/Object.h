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
	struct Pose
	{
		float x, y;
		float rotation;
	};

	class Object
	{
	public:
		Object(sf::RenderWindow *window, AssetManager *assets)
		{
			window_ = window;
			assets_ = assets;
		}
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		float getR() { return r_; }
		Pose getPose() { return pose_; }
		int getHp() { return hp_; }
		void hit(int hp) { hp_ -= hp; }
	protected:
		Pose pose_;
		float speed_;
		int hp_;
		float r_;
		float dx_, dy_;
		sf::RenderWindow *window_;
		sf::Sprite sprite_;
		AssetManager *assets_;

		virtual void move(float dt) = 0;
	};
}

#endif // !OBJECT_H