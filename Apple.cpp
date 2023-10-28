#include "Apple.h"

Apple::Apple(const sf::Vector2f& position)
{
	this->radius = 150;
	this->mass = radius * 1.5f;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color::Green);
}