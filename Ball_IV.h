#pragma once
#include "Ball.h"
#include "Ball_V.h"

class Ball_IV : virtual public Ball
{
public:
	Ball_IV(const sf::Vector2f& position)
		: Ball(BALL_IV, position, "res/Pong22.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_V(position);
	};
};

