#pragma once
#include "Ball.h"
#include "Ball_II.h"

class Ball_I : virtual public Ball
{
public:
	Ball_I(const sf::Vector2f& position)
		: Ball(BALL_I, position, "res/Pea12.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_II(position);
	};
};

