#pragma once
#include "Ball.h"
#include "Ball_IX.h"

class Ball_VIII : virtual public Ball
{
public:
	Ball_VIII(const sf::Vector2f& position)
		: Ball(BALL_VIII, position, "res/Beach36.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_IX(position);
	};
};

