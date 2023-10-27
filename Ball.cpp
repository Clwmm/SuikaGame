#include "Ball.h"

Ball::Ball(const float& radius, const sf::Vector2f& position)
{
	this->radius = radius;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
}

Ball::~Ball()
{
}

void Ball::update(float deltaTime)
{
}
