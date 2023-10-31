#pragma once
#include "Ball.h"
#include "Final.h"

class Watermelon : virtual public Ball
{
public:
	Watermelon(const sf::Vector2f& position)
		: Ball(WATERMELON_SIZE, position, "res/Basketball.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Final(position);
	};
};

