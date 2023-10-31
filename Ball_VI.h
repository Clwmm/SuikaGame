#pragma once
#include "Ball.h"
#include "Ball_VII.h"

class Ball_VI : virtual public Ball
{
public:
	Ball_VI(const sf::Vector2f& position)
		: Ball(BALL_VI, position, "res/Bawling30.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_VII(position);
	};
};

