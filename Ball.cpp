#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(const float& radius, const sf::Vector2f& position)
{
	this->radius = radius;
	this->mass = radius * 1.5f;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
}

void Ball::update(float deltaTime)
{
	/*this->acceleration = -this->velocity * 0.6f;
	this->velocity += this->acceleration * deltaTime;
	this->position += this->velocity * deltaTime;*/

	

	this->acceleration.x = -this->velocity.x * 0.6f;
	this->acceleration.y = -this->velocity.y * 0.6f;

	this->acceleration.y += 50.f * this->mass;

	this->velocity.x += this->acceleration.x * deltaTime * 0.2f;
	this->velocity.y += this->acceleration.y * deltaTime * 0.2f;

	this->position.x += this->velocity.x * deltaTime;
	this->position.y += this->velocity.y * deltaTime;

	if (this->position.y >= 1800 - this->radius)
	{
		this->position.y = 1800 - this->radius;
		this->velocity.y = -this->velocity.y * 0.1;
		this->acceleration.y = 0;
	}

	if (this->position.x >= 1100 - this->radius)
	{
		this->position.x = 1100 - this->radius;
		this->velocity.x = -this->velocity.x * 0.1;
		this->acceleration.x = 0;
	}

	if (this->position.x <= -1100 + this->radius)
	{
		this->position.x = -1100 + this->radius;
		this->velocity.x = -this->velocity.x * 0.1;
		this->acceleration.x = 0;
	}

	if (fabs(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) < 10.f)
		this->velocity = { 0, 0 };
	

}
