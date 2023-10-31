#pragma once
#include "Ball.h"
#include "Orange.h"

class Apple : virtual public Ball
{
public:
	Apple(const sf::Vector2f& position)
		: Ball(APPLE_SIZE, position, "res/Marble.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Orange(position);
	};
};

