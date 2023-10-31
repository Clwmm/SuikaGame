#pragma once
#include "Ball.h"
#include "Melon.h"

class Orange : virtual public Ball
{
public:
	Orange(const sf::Vector2f& position)
		:Ball(ORANGE_SIZE, position, "res/Pong.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Melon(position);
	};
};

