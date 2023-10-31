#pragma once
#include "Ball.h"

class Final : virtual public Ball
{
public:
	Final(const sf::Vector2f& position)
		: Ball(FINAL_SIZE, position, "res/Planet.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return nullptr;
	};
};
