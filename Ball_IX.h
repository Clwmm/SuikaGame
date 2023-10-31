#pragma once
#include "Ball.h"
#include "Ball_X.h"

class Ball_IX : virtual public Ball
{
public:
	Ball_IX(const sf::Vector2f& position)
		: Ball(BALL_IX, position, "res/Moon40.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_X(position);
	};
};