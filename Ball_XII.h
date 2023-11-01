#pragma once
#include "Ball.h"

class Ball_XII : virtual public Ball
{
public:
	Ball_XII(const sf::Vector2f& position)
		: Ball(BALL_XII, position, "res/Blackhole48.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return nullptr;
	};
};