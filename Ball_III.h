#pragma once
#include "Ball.h"
#include "Ball_IV.h"

class Ball_III : virtual public Ball
{
public:
	Ball_III(const sf::Vector2f& position)
		: Ball(BALL_III, position, "res/Eyeball18.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_IV(position);
	};
};

