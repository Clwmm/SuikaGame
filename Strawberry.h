#pragma once
#include "Ball.h"
#include "Apple.h"

class Strawberry : virtual public Ball
{
public:
	Strawberry(const sf::Vector2f& position)
		: Ball(STRAWBERRY_SIZE, position, "res/Pea.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Apple(position);
	};
};

