#include "Strawberry.h"

Strawberry::Strawberry(const sf::Vector2f& position)
{
	this->radius = STRAWBERRY_SIZE;
	this->mass = radius * MASS_MULTIPLIER;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color::Red);


	if (!texture.loadFromFile("res/Pea.png"))
	{
		std::cerr << "Cannot load: " << "res/Pea.png" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}