#include "Apple.h"

Apple::Apple(const sf::Vector2f& position)
{
	this->radius = APPLE_SIZE;
	this->mass = radius * MASS_MULTIPLIER;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color::Green);

	if (!texture.loadFromFile("res/Marble.png"))
	{
		std::cerr << "Cannot load: " << "res/Marble.png" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}