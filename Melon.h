#pragma once
#include "Ball.h"
#include "Watermelon.h"

class Melon : virtual public Ball
{
public:
	Melon(const sf::Vector2f& position)
		:Ball(MELON_SIZE, position, "res/Tenis.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Watermelon(position);
	};
};

