#pragma once
#include "Ball.h"
#include "Ball_XI.h"

class Ball_X : virtual public Ball
{
public:
	Ball_X(const sf::Vector2f& position)
		: Ball(BALL_X, position, "res/Planet42.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_XI(position);
	};
};