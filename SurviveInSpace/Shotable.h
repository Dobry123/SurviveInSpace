#pragma once
#ifndef SHOTABLE_H
#define SHOTABLE_H

#include "Object.h"
#include "Shot.h"

namespace sis
{
	class Shotable :public Object
	{
	public:
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
	protected:
		//virtual void shot() = 0;
		virtual void move(float dt) = 0;
		int shot_amount_;
	};
}

#endif // !SHOTABLE_H