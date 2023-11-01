#pragma once
#include "Ball.h"
#include "Ball_XII.h"

class Ball_XI : virtual public Ball
{
public:
	Ball_XI(const sf::Vector2f& position)
		: Ball(BALL_XI, position, "res/Galaxy44.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_XII(position);
	};
};