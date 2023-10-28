#include "Orange.h"

Orange::Orange(const sf::Vector2f& position)
{
	this->radius = 200;
	this->mass = radius * 1.5f;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color(255, 165, 0));
}
