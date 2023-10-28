#pragma once
#include "Ball.h"

class Apple : virtual public Ball
{
public:
	Apple(const sf::Vector2f& position);
};

