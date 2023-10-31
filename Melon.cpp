#include "Melon.h"

Melon::Melon(const sf::Vector2f& position)
{
	this->radius = MELON_SIZE;
	this->mass = radius * MASS_MULTIPLIER;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color(200, 255, 0));

	if (!texture.loadFromFile("res/Tenis.png"))
	{
		std::cerr << "Cannot load: " << "res/Tenis.png" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
