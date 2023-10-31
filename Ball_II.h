#pragma once
#include "Ball.h"
#include "Ball_III.h"

class Ball_II : virtual public Ball
{
public:
	Ball_II(const sf::Vector2f& position)
		: Ball(BALL_II, position, "res/Bilard16.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_III(position);
	};
};

