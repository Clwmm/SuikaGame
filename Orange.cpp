#include "Orange.h"

Orange::Orange(const sf::Vector2f& position)
{
	this->radius = ORANGE_SIZE;
	this->mass = radius * MASS_MULTIPLIER;
	this->position = position;

	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color(255, 165, 0));

	if (!texture.loadFromFile("res/Pong.png"))
	{
		std::cerr << "Cannot load: " << "res/Pong.png" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
