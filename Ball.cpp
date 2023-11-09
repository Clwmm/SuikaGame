#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(const float& radius, const sf::Vector2f& position, std::string textureName)
{
	this->radius = radius;
	this->mass = radius * MASS_MULTIPLIER;
	this->position = position;

	texture = TextureManager::AcquireTexture(textureName);

	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

void Ball::update(float deltaTime)
{
	this->acceleration.x = -this->velocity.x * A_SLOWDOWN_MULITPLIER;
	this->acceleration.y = -this->velocity.y * A_SLOWDOWN_MULITPLIER;

	this->acceleration.y += GRAVITI_MULITPLIER * this->mass;

	this->velocity.x += this->acceleration.x * deltaTime * V_SLOWDOWN_MULITPLIER;
	this->velocity.y += this->acceleration.y * deltaTime * V_SLOWDOWN_MULITPLIER;

	this->position.x += this->velocity.x * deltaTime;
	this->position.y += this->velocity.y * deltaTime;

	if (this->position.y >= Y_BOUNDRY - this->radius)
	{
		this->position.y = Y_BOUNDRY - this->radius;
		this->velocity.y = -this->velocity.y * 0.2f;
		this->acceleration.y = 0;
	}

	if (this->position.x >= X_BOUNDRY - this->radius)
	{
		this->position.x = X_BOUNDRY - this->radius;
		this->velocity.x = -this->velocity.x * 0.2f;
		this->acceleration.x = 0;
	}

	if (this->position.x <= -X_BOUNDRY + this->radius)
	{
		this->position.x = -X_BOUNDRY + this->radius;
		this->velocity.x = -this->velocity.x * 0.2f;
		this->acceleration.x = 0;
	}

	if (fabs(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) < 0.1f)
		this->velocity = { 0, 0 };
	
	this->sprite.rotate(this->velocity.x * 2.5f * deltaTime);
}
