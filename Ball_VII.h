#pragma once
#include "Ball.h"
#include "Ball_VIII.h"

class Ball_VII : virtual public Ball
{
public:
	Ball_VII(const sf::Vector2f& position)
		: Ball(BALL_VII, position, "res/Basketball32.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_VIII(position);
	};
};

