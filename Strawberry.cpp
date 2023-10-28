#include "Strawberry.h"

Strawberry::Strawberry(const sf::Vector2f& position)
{
	this->radius = 100;
	this->mass = radius * 1.5f;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color::Red);
}