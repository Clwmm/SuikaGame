#pragma once
#include "Ball.h"
#include "Ball_VI.h"

class Ball_V : virtual public Ball
{
public:
	Ball_V(const sf::Vector2f& position)
		: Ball(BALL_V, position, "res/Tenis26.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_VI(position);
	};
};

