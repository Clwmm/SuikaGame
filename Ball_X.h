#pragma once
#include "Ball.h"

class Ball_X : virtual public Ball
{
public:
	Ball_X(const sf::Vector2f& position)
		: Ball(BALL_IX, position, "res/Planet42.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return nullptr;
	};
};