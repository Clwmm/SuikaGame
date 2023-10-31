#include "Final.h"

Final::Final(const sf::Vector2f& position)
{
	this->radius = FINAL_SIZE;
	this->mass = radius * MASS_MULTIPLIER;
	this->position = position;

	/*this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color(255, 0, 255));*/

	if (!texture.loadFromFile("res/Planet.png"))
	{
		std::cerr << "Cannot load: " << "res/Planet.png" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
